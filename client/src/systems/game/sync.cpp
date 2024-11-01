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

using namespace rtype::client::systems;
using namespace rtype::client::components;
using namespace rtype::client::services;
using namespace zygarde::core::components;
using namespace zygarde::core::types;
using namespace mew::sets::drawable;

BlinkSystem::BlinkSystem(ServerConnectionService::Ptr server_connection_service)
    : ASystem(), serverConnectionService_{std::move(server_connection_service)} {}

void BlinkSystem::Run(Registry::Ptr r) {
  auto queue = serverConnectionService_->client()->ExtractQueue();
  while (!queue.empty()) {
    auto& message = queue.front();
    HandleMessage(r, message);
    queue.pop();
  }
}

void BlinkSystem::CreatePlayer(const std::shared_ptr<Registry>& registry, const std::size_t& id,
                                  const Vector3f& pos) {
  auto player = registry->SpawnEntity();
  static const sf::IntRect base{100, 0, 32, 16};

  registry->AddComponent<ServerEntityId>(player, {.id = id});
  registry->AddComponent<Position>(
      player, {.point = pos, .aligns = {HorizontalAlign::kLeft, VerticalAlign::kTop}});
  registry->AddComponent<Drawable>(
      player, {
                  .drawable = Texture{.name = "player", .scale = 2.9, .rect = base},
              });

  std::cout << "Player created" << std::endl;
  players_.insert_or_assign(id, player);
}

void BlinkSystem::UpdatePlayer(const std::shared_ptr<Registry>& registry, const std::size_t& id,
                                  const Vector3f& pos) {
  auto player = players_.at(id);
  auto positions = registry->GetComponents<Position>();
  auto entity_id = static_cast<std::size_t>(player);

  if (entity_id >= positions->size()) {
    std::cerr << "Invalid player id" << std::endl;
    return;
  }
  if ((*positions)[entity_id]) {
    (*positions)[entity_id]->point = pos;
  }
}

void BlinkSystem::CreateBullet(const std::shared_ptr<Registry>& registry,
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
  bullets_.insert_or_assign(state.entityId, bullet);
}

void BlinkSystem::UpdateBullet(const std::shared_ptr<Registry>& registry, const std::size_t& id,
                                  const Vector3f& pos) {
  auto bullet = bullets_.at(id);
  auto positions = registry->GetComponents<Position>();
  auto entity_id = static_cast<std::size_t>(bullet);

  if (entity_id >= positions->size()) {
    std::cerr << "Invalid bullet id" << std::endl;
    return;
  }
  if ((*positions)[entity_id]) {
    (*positions)[entity_id]->point = pos;
  }
}

void BlinkSystem::CreateEnemy(const std::shared_ptr<Registry>& registry, const std::size_t& id,
                                 const Vector3f& pos) {
  auto enemy = registry->SpawnEntity();
  static const sf::IntRect base{5, 6, 21, 36};

  registry->AddComponent<ServerEntityId>(enemy, {.id = id});
  registry->AddComponent<Position>(
      enemy, {.point = pos, .aligns = {HorizontalAlign::kLeft, VerticalAlign::kTop}});
  registry->AddComponent<Drawable>(
      enemy, {
                 .drawable = Texture{.name = "enemy", .scale = 2.5, .rect = base},
             });
  enemies_.insert_or_assign(id, enemy);
}

void BlinkSystem::UpdateEnemy(const std::shared_ptr<Registry>& registry, const std::size_t& id,
                                 const Vector3f& pos) {
  auto enemy = enemies_.at(id);
  auto positions = registry->GetComponents<Position>();
  auto entity_id = static_cast<std::size_t>(enemy);

  if (entity_id >= positions->size()) {
    std::cerr << "Invalid enemy id" << std::endl;
    return;
  }
  if ((*positions)[entity_id]) {
    (*positions)[entity_id]->point = pos;
  }
}

void BlinkSystem::HandleMessage(const Registry::Ptr& registry,
                                   const api::Client::ServerMessage& message) {
  switch (message.messageType) {
    case api::RoomToClientMsgType::kMsgTypeRTCPlayersState:
      return HandlePlayers(registry, message);
    case api::RoomToClientMsgType::kMsgTypeRTCBulletsState:
      return HandleBullets(registry, message);
    case api::RoomToClientMsgType::kMsgTypeRTCEnemiesState:
      return HandleEnemies(registry, message);
  }
}

void BlinkSystem::HandlePlayers(const Registry::Ptr& registry,
                                   const api::Client::ServerMessage& message) {
  auto states = serverConnectionService_->client()->ResolvePlayersState(message);
  auto handled = std::set<std::size_t>();

  for (const auto& state : states) {
    HandlePlayerState(registry, state, &handled);
  }
  DeleteEntities(registry, handled, &players_);
}

void BlinkSystem::HandlePlayerState(const Registry::Ptr& registry,
                                       const api::payload::PlayerState& state,
                                       std::set<std::size_t>* handled) {
  if (players_.contains(state.entityId)) {
    UpdatePlayer(registry, state.entityId, Vector3f{state.position.x, state.position.y});
  } else {
    CreatePlayer(registry, state.entityId, Vector3f{state.position.x, state.position.y});
  }
  handled->insert(state.entityId);
}

void BlinkSystem::HandleBullets(const Registry::Ptr& registry,
                                   const api::Client::ServerMessage& message) {
  auto states = serverConnectionService_->client()->ResolveBulletsState(message);
  auto handled = std::set<std::size_t>();

  for (const auto& state : states) {
    HandleBulletState(registry, state, &handled);
  }
  DeleteEntities(registry, handled, &bullets_);
}

void BlinkSystem::HandleBulletState(const Registry::Ptr& registry,
                                       const api::payload::BulletState& state,
                                       std::set<std::size_t>* handled) {
  if (bullets_.contains(state.entityId)) {
    UpdateBullet(registry, state.entityId, Vector3f{state.position.x, state.position.y});
  } else {
    CreateBullet(registry, state);
  }
  handled->insert(state.entityId);
}

void BlinkSystem::HandleEnemies(const Registry::Ptr& registry,
                                   const api::Client::ServerMessage& message) {
  auto states = serverConnectionService_->client()->ResolveEnemiesState(message);
  auto handled = std::set<std::size_t>();

  for (const auto& state : states) {
    HandleEnemyState(registry, state, &handled);
  }
  DeleteEntities(registry, handled, &enemies_);
}

void BlinkSystem::HandleEnemyState(const Registry::Ptr& registry,
                                      const api::payload::EnemyState& state,
                                      std::set<std::size_t>* handled) {
  if (enemies_.contains(state.entityId)) {
    UpdateEnemy(registry, state.entityId, Vector3f{state.position.x, state.position.y});
  } else {
    CreateEnemy(registry, state.entityId, Vector3f{state.position.x, state.position.y});
  }
  handled->insert(state.entityId);
}

void BlinkSystem::DeleteEntities(const Registry::Ptr& registry,
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
