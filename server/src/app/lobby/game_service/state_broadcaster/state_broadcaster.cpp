/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** state_broadcaster.cpp
*/

#include "state_broadcaster.hpp"

#include "constants/tags.hpp"
#include "core/components/position/position.hpp"

using namespace rtype::server::game;

void StateBroadcaster::Run(const std::shared_ptr<zygarde::Registry>& registry,
                           const std::shared_ptr<rtype::sdk::game::api::Lobby>& api) {
  std::unique_ptr<EntityStates> entityStates = std::make_unique<EntityStates>();

  GatherEntityStates(registry, entityStates);
  SendStates(api, entityStates);
}

void StateBroadcaster::GatherEntityStates(const std::shared_ptr<zygarde::Registry>& registry,
                                          const std::unique_ptr<EntityStates>& states) noexcept {
  const auto components = registry->GetComponents<core::components::Position>();
  std::size_t i = 0;

  for (auto& component : *components) {
    if (!registry->HasEntityAtIndex(i) || !component.has_value()) {
      i++;
      continue;
    }

    const auto val = component.value();
    auto ent = registry->EntityFromIndex(i);
    const sdk::game::utils::types::vector_2f vec = {val.point.x, val.point.y};
    const auto tags = registry->GetComponent<core::components::Tags>(ent);
    if (tags.has_value() && tags.value()) {
      ProcessEntity(states, ent, vec, *tags);
    }
    i++;
  }
}

void StateBroadcaster::ProcessEntity(const std::unique_ptr<EntityStates>& states,
                                     const Entity& entity,
                                     const rtype::sdk::game::utils::types::vector_2f& vec,
                                     const core::components::Tags* tags) noexcept {
  const core::components::Tags tagsToCheck{*tags};
  if (tagsToCheck & sdk::game::constants::kPlayerTag) {
    payload::PlayerState state = {static_cast<std::size_t>(entity), vec, 100};
    std::cout << "Player state: " << state.entityId << std::endl;
    std::cout << "Player state: " << state.position.x << " " << state.position.y << std::endl;
    states->playerStates.push_back(state);
  }
  if (tagsToCheck & sdk::game::constants::kEnemyTag) {
    GatherEnemyState(states, entity, vec, &tagsToCheck);
  }
  if (tagsToCheck & sdk::game::constants::kBulletTag) {
    GatherProjectileState(states, entity, vec, &tagsToCheck);
  }
}

void StateBroadcaster::SendStates(const std::shared_ptr<rtype::sdk::game::api::Lobby>& api,
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
                                        const zygarde::Entity& entity,
                                        const sdk::game::utils::types::vector_2f& vec,
                                        const core::components::Tags* tags) noexcept {
  if (*tags == sdk::game::constants::kPataTag) {
    payload::EnemyState state = {static_cast<std::size_t>(entity), vec,
                                 sdk::game::types::EnemyType::kPata, 100};
    states->enemyStates.push_back(state);
  }
}

void StateBroadcaster::GatherProjectileState(const std::unique_ptr<EntityStates>& states,
                                             const zygarde::Entity& entity,
                                             const sdk::game::utils::types::vector_2f& vec,
                                             const core::components::Tags* tags) noexcept {
  if (*tags == sdk::game::constants::kPlayerBulletTag) {
    payload::BulletState state = {static_cast<std::size_t>(entity), vec,
                                  sdk::game::types::ProjectileType::kPlayerCommon};
    states->bulletStates.push_back(state);
  }
  if (*tags == sdk::game::constants::kEnemyBulletTag) {
    payload::BulletState state = {static_cast<std::size_t>(entity), vec,
                                  sdk::game::types::ProjectileType::kEnemyCommon};
    states->bulletStates.push_back(state);
  }
}
