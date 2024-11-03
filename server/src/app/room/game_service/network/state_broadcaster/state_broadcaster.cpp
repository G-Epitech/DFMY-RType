/*
 ** EPITECH PROJECT, 2024
 ** r-type
 ** File description:
 ** state_broadcaster.cpp
 */

#include "state_broadcaster.hpp"

#include "constants/tags.hpp"
#include "core/components/position/position.hpp"

using namespace rtype::server::game::network;

void StateBroadcaster::Run(const std::shared_ptr<Registry>& registry,
                           const std::shared_ptr<Room>& api) {
  std::unique_ptr<EntityStates> entityStates = std::make_unique<EntityStates>();

  GatherEntityStates(registry, entityStates);
  SendStates(api, entityStates);
}

void StateBroadcaster::GatherEntityStates(const std::shared_ptr<Registry>& registry,
                                          const std::unique_ptr<EntityStates>& states) noexcept {
  const auto positions = registry->GetComponents<Position>();
  std::size_t i = 0;

  for (auto& position : *positions) {
    if (!registry->HasEntityAtIndex(i) || !position.has_value()) {
      i++;
      continue;
    }

    const auto [point, aligns] = position.value();
    auto entity = registry->EntityFromIndex(i);
    const auto tags = registry->GetComponent<Tags>(entity);
    const auto rigidbodies = registry->GetComponent<Rigidbody2D>(entity);
    if (tags.has_value() && tags.value() && rigidbodies.has_value() && rigidbodies.value()) {
      ProcessEntity(states, entity, point, *tags, *rigidbodies);
    }
    i++;
  }
}

void StateBroadcaster::ProcessEntity(const std::unique_ptr<EntityStates>& states,
                                     const Entity& entity, const Vector3f& position,
                                     const Tags* tags, const Rigidbody2D* rigidbodies) noexcept {
  const Tags tagsToCheck{*tags};
  const core::types::Vector2f velocity = rigidbodies->GetVelocity();
  if (tagsToCheck & sdk::game::constants::kPlayerTag) {
    const payload::PlayerState state = {static_cast<std::size_t>(entity), position, 100, velocity};
    states->playerStates.push_back(state);
  }
  if (tagsToCheck & sdk::game::constants::kEnemyTag) {
    GatherEnemyState(states, entity, position, velocity, &tagsToCheck);
  }
  if (tagsToCheck & sdk::game::constants::kBulletTag) {
    GatherProjectileState(states, entity, position, velocity, &tagsToCheck);
  }
}

void StateBroadcaster::SendStates(const std::shared_ptr<Room>& api,
                                  const std::unique_ptr<EntityStates>& states) {
  if (states->playerStates.empty()) {
    AddDummyPlayerState(states);
  }
  if (states->enemyStates.empty()) {
    AddDummyEnemyState(states);
  }
  if (states->bulletStates.empty()) {
    AddDummyBulletState(states);
  }
  api->SendBulletsState(states->bulletStates);
  api->SendEnemiesState(states->enemyStates);
  api->SendPlayersState(states->playerStates);
}
void StateBroadcaster::GatherEnemyState(const std::unique_ptr<EntityStates>& states,
                                        const Entity& entity, const Vector3f& position,
                                        const Vector2f& velocity, const Tags* tags) noexcept {
  auto enemyType = GetEnemyType(tags);
  const payload::EnemyState state = {static_cast<std::size_t>(entity), position, velocity,
                                     enemyType, 100};

  states->enemyStates.push_back(state);
}

rtype::sdk::game::types::EnemyType StateBroadcaster::GetEnemyType(
    const Tags* entity_tags) noexcept {
  for (const auto& [enemyName, type] : kEnemyTypeMap_) {
    if (*entity_tags & enemyName) {
      return type;
    }
  }
  return sdk::game::types::EnemyType::kPata;
}

void StateBroadcaster::GatherProjectileState(const std::unique_ptr<EntityStates>& states,
                                             const Entity& entity, const Vector3f& position,
                                             const Vector2f& velocity, const Tags* tags) noexcept {
  auto projectileType = GetProjectileType(tags);

  const payload::BulletState state = {static_cast<std::size_t>(entity), position, velocity,
                                      projectileType};
  states->bulletStates.push_back(state);
}

rtype::sdk::game::types::ProjectileType StateBroadcaster::GetProjectileType(
    const Tags* entity_tags) noexcept {
  for (const auto& [bulletName, type] : kProjectileTypeMap_) {
    if (*entity_tags & bulletName) {
      return type;
    }
  }
  return sdk::game::types::ProjectileType::kPlayerCommon;
}

void StateBroadcaster::AddDummyBulletState(const std::unique_ptr<EntityStates>& states) noexcept {
  static constexpr api::payload::BulletState dummyBullet = {
      .entityId = 10000,
      .position = Vector3f{10000, 10000, 10000},
      .velocity = {0, 0},
      .bulletType = sdk::game::types::ProjectileType::kPlayerCommon,
  };
  states->bulletStates.push_back(dummyBullet);
}
void StateBroadcaster::AddDummyPlayerState(const std::unique_ptr<EntityStates>& states) noexcept {
  static constexpr api::payload::PlayerState dummyPlayer = {
      .entityId = 10000,
      .position = Vector3f{10000, 10000, 10000},
      .health = 100,
      .velocity = {0, 0},
  };
  states->playerStates.push_back(dummyPlayer);
}

void StateBroadcaster::AddDummyEnemyState(const std::unique_ptr<EntityStates>& states) noexcept {
  static constexpr api::payload::EnemyState dummyEnemy = {
      .entityId = 10000,
      .position = Vector3f{10000, 10000, 10000},
      .velocity = {0, 0},
      .enemyType = sdk::game::types::EnemyType::kPata,
      .health = 100,
  };

  states->enemyStates.push_back(dummyEnemy);
}
