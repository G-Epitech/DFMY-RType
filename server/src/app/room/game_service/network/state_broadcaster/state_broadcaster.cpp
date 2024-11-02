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
  if (!states->playerStates.empty()) {
    api->SendPlayersState(states->playerStates);
  }
  if (!states->enemyStates.empty()) {
    api->SendEnemiesState(states->enemyStates);
  }
  if (!states->bulletStates.empty()) {
    api->SendBulletsState(states->bulletStates);
  }
}
void StateBroadcaster::GatherEnemyState(const std::unique_ptr<EntityStates>& states,
                                        const Entity& entity, const Vector3f& position,
                                        const Vector2f& velocity, const Tags* tags) noexcept {
  if (*tags == sdk::game::constants::kPataTag) {
    const payload::EnemyState state = {static_cast<std::size_t>(entity), position, velocity,
                                       sdk::game::types::EnemyType::kPata, 100};
    states->enemyStates.push_back(state);
  }
  if (*tags == sdk::game::constants::kPataBigTag) {
    payload::EnemyState state = {static_cast<std::size_t>(entity), position, velocity,
                                 sdk::game::types::EnemyType::kPataBig, 100};
    states->enemyStates.push_back(state);
  }
}

void StateBroadcaster::GatherProjectileState(const std::unique_ptr<EntityStates>& states,
                                             const Entity& entity, const Vector3f& position,
                                             const Vector2f& velocity, const Tags* tags) noexcept {
  if (*tags == sdk::game::constants::kPlayerBulletTag) {
    const payload::BulletState state = {static_cast<std::size_t>(entity), position, velocity,
                                        sdk::game::types::ProjectileType::kPlayerCommon};
    states->bulletStates.push_back(state);
  }
  if (*tags == sdk::game::constants::kEnemyBulletTag) {
    const payload::BulletState state = {static_cast<std::size_t>(entity), position, velocity,
                                        sdk::game::types::ProjectileType::kEnemyCommon};
    states->bulletStates.push_back(state);
  }
}
