/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** sync.cpp
*/

#include "sync.hpp"

#include <set>
#include <utility>

#include "components/drawable.hpp"
#include "libs/zygarde/src/core/components/position/position.hpp"

using namespace rtype::client::systems;
using namespace rtype::client::components;
using namespace zygarde::core::components;
using namespace zygarde::core::types;

GameSyncSystem::GameSyncSystem(ServerConnectionManager::Ptr serverConnectionManager)
    : serverConnectionManager_{std::move(serverConnectionManager)} {}

void GameSyncSystem::Run(Registry::Ptr r, sparse_array<components::ServerEntityId>::ptr IDs) {
  auto queue = serverConnectionManager_->client()->ExtractQueue();
  while (!queue.empty()) {
    auto& message = queue.front();
    HandleMessage(r, message);
    queue.pop();
  }
}

void GameSyncSystem::CreatePlayer(const std::shared_ptr<Registry>& registry, const std::size_t& id,
                                  const zygarde::core::types::Vector3f& pos) {
  auto player = registry->SpawnEntity();
  static const sf::IntRect base{100, 0, 32, 16};

  registry->AddComponent<components::ServerEntityId>(player, {.id = id});
  registry->AddComponent<zygarde::core::components::Position>(
      player, {.point = pos,
               .aligns = {core::components::HorizontalAlign::kLeft,
                          core::components::VerticalAlign::kTop}});
  registry->AddComponent<components::Drawable>(
      player, {
                  .drawable = components::Texture{.name = "player", .scale = 5, .rect = base},
              });

  std::cout << "Player created" << std::endl;
  players_.insert_or_assign(id, player);
}

void GameSyncSystem::UpdatePlayer(const std::shared_ptr<Registry>& registry, const std::size_t& id,
                                  const zygarde::core::types::Vector3f& pos) {
  auto player = players_.at(id);
  auto positions = registry->GetComponents<zygarde::core::components::Position>();
  auto entity_id = static_cast<std::size_t>(player);

  if (entity_id >= positions->size()) {
    std::cerr << "Invalid player id" << std::endl;
    return;
  }
  if ((*positions)[entity_id]) {
    (*positions)[entity_id]->point = pos;
  }
}

void GameSyncSystem::CreateBullet(const std::shared_ptr<Registry>& registry, const std::size_t& id,
                                  const zygarde::core::types::Vector3f& pos) {
  const auto bullet = registry->SpawnEntity();
  static const sf::IntRect base{337, 255, 12, 4};

  registry->AddComponent<components::ServerEntityId>(bullet, {.id = id});
  registry->AddComponent<zygarde::core::components::Position>(
      bullet, {.point = pos,
               .aligns = {core::components::HorizontalAlign::kLeft,
                          core::components::VerticalAlign::kTop}});
  registry->AddComponent<components::Drawable>(
      bullet, {
                  .drawable = components::Texture{.name = "bullet", .scale = 3, .rect = base},
              });
  bullets_.insert_or_assign(id, bullet);
}

void GameSyncSystem::UpdateBullet(const std::shared_ptr<Registry>& registry, const std::size_t& id,
                                  const zygarde::core::types::Vector3f& pos) {
  auto bullet = bullets_.at(id);
  auto positions = registry->GetComponents<zygarde::core::components::Position>();
  auto entity_id = static_cast<std::size_t>(bullet);

  if (entity_id >= positions->size()) {
    std::cerr << "Invalid bullet id" << std::endl;
    return;
  }
  if ((*positions)[entity_id]) {
    (*positions)[entity_id]->point = pos;
  }
}

void GameSyncSystem::CreateEnemy(const std::shared_ptr<Registry>& registry, const std::size_t& id,
                                 const zygarde::core::types::Vector3f& pos) {
  auto enemy = registry->SpawnEntity();
  static const sf::IntRect base{0, 0, 33, 36};

  registry->AddComponent<components::ServerEntityId>(enemy, {.id = id});
  registry->AddComponent<zygarde::core::components::Position>(
      enemy, {.point = pos,
              .aligns = {core::components::HorizontalAlign::kLeft,
                         core::components::VerticalAlign::kTop}});
  registry->AddComponent<components::Drawable>(
      enemy, {
                 .drawable = components::Texture{.name = "enemy", .scale = 3, .rect = base},
             });
  enemies_.insert_or_assign(id, enemy);
}

void GameSyncSystem::UpdateEnemy(const std::shared_ptr<Registry>& registry, const std::size_t& id,
                                 const zygarde::core::types::Vector3f& pos) {
  auto enemy = enemies_.at(id);
  auto positions = registry->GetComponents<zygarde::core::components::Position>();
  auto entity_id = static_cast<std::size_t>(enemy);

  if (entity_id >= positions->size()) {
    std::cerr << "Invalid enemy id" << std::endl;
    return;
  }
  if ((*positions)[entity_id]) {
    (*positions)[entity_id]->point = pos;
  }
}

void GameSyncSystem::HandleMessage(const Registry::Ptr& registry,
                                   const api::Client::ServerMessage& message) {
  switch (message.messageType) {
    case api::MessageServerType::kPlayersState:
      return HandlePlayers(registry, message);
    case api::MessageServerType::kBulletsState:
      return HandleBullets(registry, message);
    case api::MessageServerType::kEnemiesState:
      return HandleEnemies(registry, message);
  }
}

void GameSyncSystem::HandlePlayers(const Registry::Ptr& registry,
                                   const api::Client::ServerMessage& message) {
  auto states = serverConnectionManager_->client()->ResolvePlayersState(message);
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
    UpdatePlayer(registry, state.entityId, Vector3f{state.position.x, state.position.y});
  } else {
    CreatePlayer(registry, state.entityId, Vector3f{state.position.x, state.position.y});
  }
  handled->insert(state.entityId);
}

void GameSyncSystem::HandleBullets(const Registry::Ptr& registry,
                                   const api::Client::ServerMessage& message) {
  auto states = serverConnectionManager_->client()->ResolveBulletsState(message);
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
    UpdateBullet(registry, state.entityId, Vector3f{state.position.x, state.position.y});
  } else {
    CreateBullet(registry, state.entityId, Vector3f{state.position.x, state.position.y});
  }
  handled->insert(state.entityId);
}

void GameSyncSystem::HandleEnemies(const Registry::Ptr& registry,
                                   const api::Client::ServerMessage& message) {
  auto states = serverConnectionManager_->client()->ResolveEnemiesState(message);
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
    UpdateEnemy(registry, state.entityId, Vector3f{state.position.x, state.position.y});
  } else {
    CreateEnemy(registry, state.entityId, Vector3f{state.position.x, state.position.y});
  }
  handled->insert(state.entityId);
}

void GameSyncSystem::DeleteEntities(const Registry::Ptr& registry,
                                    const std::set<std::size_t>& handled,
                                    std::map<std::size_t, Entity>* entities) {
  for (const auto& [id, entity] : *entities) {
    if (handled.find(id) == handled.end()) {
      registry->KillEntity(entity);
      entities->erase(id);
    }
  }
}
