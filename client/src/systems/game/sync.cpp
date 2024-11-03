/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** sync.cpp
*/

#include "sync.hpp"

#include <set>
#include <utility>

#include "client/src/services/server_connection_service.hpp"
#include "client/src/systems/game/texture_mapper/texture_mapper.hpp"
#include "libs/mew/src/sets/drawable/drawable.hpp"
#include "libs/zygarde/src/core/components/components.hpp"
#include "physics/2d/components/rigidbody/rigidbody_2d.hpp"

using namespace rtype::client::systems;
using namespace rtype::client::components;
using namespace rtype::client::services;
using namespace zygarde::core::components;
using namespace zygarde::core::types;
using namespace mew::sets::drawable;

GameSyncSystem::GameSyncSystem(ServerConnectionService::Ptr server_connection_service)
    : ASystem(), serverConnectionService_{std::move(server_connection_service)} {}

void GameSyncSystem::Run(Registry::Ptr r) {
  auto queue = serverConnectionService_->client()->ExtractQueue();
  while (!queue.empty()) {
    auto& message = queue.front();
    HandleMessage(r, message);
    queue.pop();
  }
}

void GameSyncSystem::CreatePlayer(const std::shared_ptr<Registry>& registry,
                                  const api::payload::PlayerState& state) {
  auto player = registry->SpawnEntity();
  static const sf::IntRect base{100, 0, 32, 16};

  registry->AddComponent<ServerEntityId>(player, {.id = state.entityId});
  registry->AddComponent<Position>(
      player, {.point = state.position, .aligns = {HorizontalAlign::kLeft, VerticalAlign::kTop}});
  registry->AddComponent<Drawable>(
      player, {
                  .drawable = Texture{.name = "player", .scale = 2.9, .rect = base},
              });
  registry->AddComponent<physics::components::Rigidbody2D>(
      player, physics::components::Rigidbody2D(state.velocity, PLAYER_KINEMATIC, PLAYER_DRAG));

  std::cout << "Player created" << std::endl;
  players_.insert_or_assign(state.entityId, player);
}

void GameSyncSystem::UpdatePlayer(const std::shared_ptr<Registry>& registry,
                                  const api::payload::PlayerState& state) {
  const auto player = players_.at(state.entityId);
  const auto entity_id = static_cast<std::size_t>(player);
  const auto positions = registry->GetComponents<Position>();
  const auto rigidbodies = registry->GetComponents<physics::components::Rigidbody2D>();

  if (entity_id >= positions->size() || entity_id >= rigidbodies->size()) {
    std::cerr << "Invalid player id" << std::endl;
    return;
  }
  if ((*positions)[entity_id] && (*rigidbodies)[entity_id]) {
    (*positions)[entity_id]->point = state.position;
    (*rigidbodies)[entity_id]->SetVelocity({state.velocity.x, state.velocity.y});
  }
}

void GameSyncSystem::CreateBullet(const std::shared_ptr<Registry>& registry,
                                  const sdk::game::api::payload::BulletState& state) {
  const auto bullet = registry->SpawnEntity();
  const auto pos = Vector3f(state.position.x, state.position.y, 0);

  registry->AddComponent<components::ServerEntityId>(bullet, {.id = state.entityId});
  registry->AddComponent<zygarde::core::components::Position>(
      bullet, {.point = pos,
               .aligns = {core::components::HorizontalAlign::kLeft,
                          core::components::VerticalAlign::kTop}});
  registry->AddComponent<Drawable>(bullet,
                                   {
                                       .drawable = TextureMapper::MapBulletType(state.bulletType),
                                   });
  registry->AddComponent<physics::components::Rigidbody2D>(
      bullet, physics::components::Rigidbody2D(state.velocity, BULLET_KINEMATIC, BULLET_DRAG));
  bullets_.insert_or_assign(state.entityId, bullet);
}

void GameSyncSystem::UpdateBullet(const std::shared_ptr<Registry>& registry,
                                  const sdk::game::api::payload::BulletState& state) {
  const auto bullet = bullets_.at(state.entityId);
  const auto positions = registry->GetComponents<Position>();
  const auto entity_id = static_cast<std::size_t>(bullet);

  if (entity_id >= positions->size()) {
    std::cerr << "Invalid bullet id" << std::endl;
    return;
  }
  if ((*positions)[entity_id]) {
    (*positions)[entity_id]->point = Vector3f{state.position.x, state.position.y, 0};
  }
}

void GameSyncSystem::CreateEnemy(const std::shared_ptr<Registry>& registry,
                                 const api::payload::EnemyState& state) {
  auto enemy = registry->SpawnEntity();
  static const sf::IntRect base{5, 6, 21, 36};

  registry->AddComponent<ServerEntityId>(enemy, {.id = state.entityId});
  registry->AddComponent<Position>(
      enemy, {.point = state.position, .aligns = {HorizontalAlign::kLeft, VerticalAlign::kTop}});
  registry->AddComponent<Drawable>(enemy,
                                   {
                                       .drawable = TextureMapper::MapEnemyType(state.enemyType),
                                   });
  registry->AddComponent<physics::components::Rigidbody2D>(
      enemy, physics::components::Rigidbody2D(state.velocity, ENEMY_KINEMATIC, ENEMY_DRAG));
  enemies_.insert_or_assign(state.entityId, enemy);
}

void GameSyncSystem::UpdateEnemy(const std::shared_ptr<Registry>& registry,
                                 const api::payload::EnemyState& state) {
  const auto enemy = enemies_.at(state.entityId);
  const auto positions = registry->GetComponents<Position>();
  const auto entity_id = static_cast<std::size_t>(enemy);

  if (entity_id >= positions->size()) {
    std::cerr << "Invalid enemy id" << std::endl;
    return;
  }
  if ((*positions)[entity_id]) {
    (*positions)[entity_id]->point = state.position;
  }
}

void GameSyncSystem::HandleMessage(const Registry::Ptr& registry,
                                   const api::Client::ServerMessage& message) {
  switch (message.messageType) {
    case api::RoomToClientMsgType::kMsgTypeRTCPlayersState:
      return HandlePlayers(registry, message);
    case api::RoomToClientMsgType::kMsgTypeRTCBulletsState:
      return HandleBullets(registry, message);
    case api::RoomToClientMsgType::kMsgTypeRTCEnemiesState:
      return HandleEnemies(registry, message);
    case api::MasterToClientMsgType::kMsgTypeMTCGameEnded:
      return HandleGameEnded(registry, message);
  }
}

void GameSyncSystem::HandlePlayers(const Registry::Ptr& registry,
                                   const api::Client::ServerMessage& message) {
  auto states = serverConnectionService_->client()->ResolvePlayersState(message);
  auto handled = std::set<std::size_t>();

  for (const auto& state : states) {
    HandlePlayerState(registry, state, &handled);
  }
  DeleteEntities(registry, handled, &players_);
}

void GameSyncSystem::HandlePlayerState(const Registry::Ptr& registry,
                                       const api::payload::PlayerState& state,
                                       std::set<std::size_t>* handled) {
  if (players_.contains(state.entityId)) {
    UpdatePlayer(registry, state);
  } else {
    CreatePlayer(registry, state);
  }
  handled->insert(state.entityId);
}

void GameSyncSystem::HandleBullets(const Registry::Ptr& registry,
                                   const api::Client::ServerMessage& message) {
  auto states = serverConnectionService_->client()->ResolveBulletsState(message);
  auto handled = std::set<std::size_t>();

  for (const auto& state : states) {
    HandleBulletState(registry, state, &handled);
  }
  DeleteEntities(registry, handled, &bullets_);
}

void GameSyncSystem::HandleBulletState(const Registry::Ptr& registry,
                                       const api::payload::BulletState& state,
                                       std::set<std::size_t>* handled) {
  if (bullets_.contains(state.entityId)) {
    UpdateBullet(registry, state);
  } else {
    CreateBullet(registry, state);
  }
  handled->insert(state.entityId);
}

void GameSyncSystem::HandleEnemies(const Registry::Ptr& registry,
                                   const api::Client::ServerMessage& message) {
  auto states = serverConnectionService_->client()->ResolveEnemiesState(message);
  auto handled = std::set<std::size_t>();

  for (const auto& state : states) {
    HandleEnemyState(registry, state, &handled);
  }
  DeleteEntities(registry, handled, &enemies_);
}

void GameSyncSystem::HandleEnemyState(const Registry::Ptr& registry,
                                      const api::payload::EnemyState& state,
                                      std::set<std::size_t>* handled) {
  if (enemies_.contains(state.entityId)) {
    UpdateEnemy(registry, state);
  } else {
    CreateEnemy(registry, state);
  }
  handled->insert(state.entityId);
}

void GameSyncSystem::DeleteEntities(const Registry::Ptr& registry,
                                    const std::set<std::size_t>& handled,
                                    std::map<std::size_t, Entity>* entities) {
  for (auto it = entities->begin(); it != entities->end();) {
    const auto& [id, entity] = *it;
    if (handled.find(id) == handled.end()) {
      registry->KillEntity(entity);
      it = entities->erase(it);
    } else {
      ++it;
    }
  }
}

void GameSyncSystem::HandleGameEnded(const Registry::Ptr &registry, const api::Client::ServerMessage &message) {
  const auto tags = registry->GetComponents<Tags>();

  std::size_t entityIndex = 0;

  for (const auto &tag : *tags) {
    if (tag && *tag & "end_fade") {
      break;
    }
    entityIndex++;
  }

  const auto entity = registry->EntityFromIndex(entityIndex);
  const auto tagsComponent = registry->GetComponent<Tags>(entity);
  if (!tagsComponent.has_value()) {
    return;
  }

  tagsComponent.value()->AddTag("fade");
}
