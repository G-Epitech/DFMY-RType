/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** GameService.cpp
*/

#include "game_service.hpp"

#include <utility>

#include "constants/tags.hpp"
#include "factories/player_factory.hpp"
#include "libs/zygarde/src/scripting/components/script/script.hpp"

using namespace rtype::server::game;
using namespace rtype::sdk::game::api;

GameService::GameService(const size_t &tick_rate)
    : ticksManager_{tick_rate}, registry_(), enemyManager_(), logger_("game-service") {}

void GameService::RegistrySetup() {
  registry_ = Registry::create();
  utils::RegistryHelper::RegisterBaseComponents(registry_);
  utils::RegistryHelper::RegisterBaseSystems(registry_, ticksManager_.DeltaTime());
}

void GameService::Initialize() {
  ticksManager_.Initialize();
  RegistrySetup();
}

int GameService::Run(std::shared_ptr<rtype::sdk::game::api::Lobby> api) {
  this->api_ = std::move(api);

  Initialize();
  while (gameRunning_) {
    ticksManager_.Update();
    HandleMessages();
    ExecuteGameLogic();
    SendStates();
    registry_->CleanupDestroyedEntities();
    ticksManager_.WaitUntilNextTick();
    std::cout << "TICK END -------------------" << std::endl;
  }
  return EXIT_SUCCESS;
}

void GameService::ExecuteGameLogic() {
  enemyManager_.Update(ticksManager_.DeltaTime(), registry_);
  registry_->RunSystems();
}

void GameService::HandleMessages() {
  auto messages = api_->ExtractQueue();

  while (!messages.empty()) {
    auto &[playerId, data] = messages.front();

    HandlePlayerMessage(playerId, data);
    messages.pop();
  }
}

void GameService::HandlePlayerMessage(const std::uint64_t &player_id,
                                      const abra::server::ClientUDPMessage &data) {
  if (data.messageType == kMovement) {
    HandlePlayerMoveMessage(player_id, data);
  }
  if (data.messageType == kShoot) {
    HandlePlayerShootMessage(player_id, data);
  }
}

void GameService::HandlePlayerMoveMessage(const std::uint64_t &player_id,
                                          const abra::server::ClientUDPMessage &data) {
  const auto packet = packetBuilder_.Build<payload::Movement>(data.bitset);
  auto &[entityId, direction] = packet->GetPayload();

  if (const auto player = players_.find(player_id); player != players_.end()) {
    const auto &playerEntity = player->second;
    const auto rigidBody = registry_->GetComponent<physics::components::Rigidbody2D>(playerEntity);

    if (!rigidBody) {
      return;
    }

    const core::types::Vector2f newDir = {direction.x, direction.y};
    rigidBody->SetVelocity(newDir * 200);
  }

  logger_.Info("Player " + std::to_string(player_id) + " moved", "🏃‍");
}

void GameService::HandlePlayerShootMessage(const std::uint64_t &player_id,
                                           const abra::server::ClientUDPMessage &data) {
  std::cout << "PLAYER " << player_id << " SAID SHOOT\n";
  auto packet = packetBuilder_.Build<payload::Shoot>(data.bitset);
  const auto player = players_.find(player_id);
  if (player != players_.end()) {
    std::cout << "PLAYER will shoot\n";
    const auto &playerEntity = player->second;
    const auto script = registry_->GetComponent<scripting::components::Script>(playerEntity);
    if (!script) {
      std::cerr << "Player does not have a script component" << std::endl;
    }
    script->SetValue("shoot", true);
  }
}

void GameService::NewPlayer(std::uint64_t player_id) {
  Entity player = PlayerFactory::CreatePlayer(
      registry_, core::types::Vector3f(487.0f, 100.0f + (100.0f * player_id), 0), {96, 48});

  players_.insert({player_id, player});
  logger_.Info("Player " + std::to_string(player_id) + " joined the game", "❇️");
}

void GameService::SendStates() const {
  const auto components = registry_->GetComponents<core::components::Position>();
  std::size_t i = 0;
  std::vector<payload::PlayerState> states;
  std::vector<payload::EnemyState> enemyStates;
  std::vector<payload::BulletState> bulletStates;

  for (auto &component : *components) {
    if (!component.has_value()) {
      i++;
      continue;
    }
    const auto val = component.value();
    if (!registry_->HasEntityAtIndex(i)) {
      i++;
      continue;
    }
    auto ent = registry_->EntityFromIndex(i);
    const sdk::game::utils::types::vector_2f vec = {val.point.x, val.point.y};
    const auto tags = registry_->GetComponent<core::components::Tags>(ent);
    if (*tags == sdk::game::constants::kPlayerTag) {
      payload::PlayerState state = {static_cast<std::size_t>(ent), vec, 100};
      states.push_back(state);
    }
    if (*tags == sdk::game::constants::kEnemyTag) {
      payload::EnemyState state = {static_cast<std::size_t>(ent), vec,
                                   sdk::game::types::EnemyType::kPata, 100};
      enemyStates.push_back(state);
    }
    if (*tags == sdk::game::constants::kPlayerBulletTag ||
        *tags == sdk::game::constants::kEnemyBulletTag) {
      payload::BulletState state = {static_cast<std::size_t>(ent), vec};
      bulletStates.push_back(state);
    }
    i++;
  }

  if (!states.empty())
    this->api_->SendPlayersState(states);
  if (!enemyStates.empty())
    this->api_->SendEnemiesState(enemyStates);
  if (!bulletStates.empty()) {
    std::cout << "sending " << bulletStates.size() << " bullets" << std::endl;
    this->api_->SendBulletsState(bulletStates);
  }
}
