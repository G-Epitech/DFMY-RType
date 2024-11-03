/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** state_broadcaster.hpp
*/

#pragma once

#include <memory>

#include "core/components/tags/tags.hpp"
#include "libs/game/includes/api.hpp"
#include "physics/2d/components/rigidbody/rigidbody_2d.hpp"
#include "registry.hpp"

using namespace zygarde::core::components;
using namespace zygarde::physics::components;

namespace rtype::server::game::network {
class StateBroadcaster final {
 public:
  StateBroadcaster() = delete;

  /**
   * Start broadcasting the state of the game to the clients of the lobby
   * @param registry Registry of the game
   * @param api API of the lobby
   */
  static void Run(const std::shared_ptr<Registry> &registry, const std::shared_ptr<Room> &api);

 private:
  /// @brief Struct to store the entity states
  struct EntityStates {
    /// @brief Player states
    std::vector<payload::PlayerState> playerStates;
    /// @brief Enemy states
    std::vector<payload::EnemyState> enemyStates;
    /// @brief Bullet states
    std::vector<payload::BulletState> bulletStates;
  };

 private:
  /**
   * @brief Gather the entity states from the registry
   * @param registry Registry of the game
   * @param states EntityStates object to store the states
   */
  static void GatherEntityStates(const std::shared_ptr<Registry> &registry,
                                 const std::unique_ptr<EntityStates> &states) noexcept;

  /**
   * Process the entity and store the states in the EntityStates object
   * @param states EntityStates object to store the states
   * @param entity Entity to process
   * @param position Position of the entity
   * @param tags Tags of the entity
   * @param rigidbodies Rigidbody of the entity
   */
  static void ProcessEntity(const std::unique_ptr<EntityStates> &states, const Entity &entity,
                            const Vector3f &position, const Tags *tags,
                            const Rigidbody2D *rigidbodies) noexcept;

  /**
   * Gather the enemy states according to their tags
   * @param states EntityStates object to store the states
   * @param entity Entity to process
   * @param position Position of the entity
   * @param velocity Velocity of the entity
   * @param tags Tags of the entity
   */
  static void GatherEnemyState(const std::unique_ptr<EntityStates> &states, const Entity &entity,
                               const Vector3f &position, const Vector2f &velocity,
                               const Tags *tags) noexcept;

  /**
   * Gather the projectile states according to their tags
   * @param states EntityStates object to store the states
   * @param entity Entity to process
   * @param position Position of the entity
   * @param velocity Velocity of the entity
   * @param tags Tags of the entity
   */
  static void GatherProjectileState(const std::unique_ptr<EntityStates> &states,
                                    const Entity &entity, const Vector3f &position,
                                    const Vector2f &velocity, const Tags *tags) noexcept;
  /**
   * Sends the states to the clients of the lobby
   * @param api API of the lobby
   * @param states EntityStates object containing the states
   */
  static void SendStates(const std::shared_ptr<Room> &api,
                         const std::unique_ptr<EntityStates> &states);

  /**
   * @brief Add a dummy bullet state to the EntityStates object
   * @param states EntityStates object to store the states
   */
  static void AddDummyBulletState(const std::unique_ptr<EntityStates> &states) noexcept;

  /**
   * @brief Add a dummy player state to the EntityStates object
   * @param states EntityStates object to store the states
   */
  static void AddDummyPlayerState(const std::unique_ptr<EntityStates> &states) noexcept;

  /**
   * @brief Add a dummy enemy state to the EntityStates object
   * @param states EntityStates object to store the states
   */
  static void AddDummyEnemyState(const std::unique_ptr<EntityStates> &states) noexcept;

  /**
   * @brief Get the enemy type from the tags
   * @param entity_tags Tags of the entity
   * @return The enemy type
   */
  static sdk::game::types::EnemyType GetEnemyType(const Tags *entity_tags) noexcept;

  /**
   * @brief Get the projectile type from the tags
   * @param entity_tags Tags of the entity
   * @return The projectile type
   */
  static sdk::game::types::ProjectileType GetProjectileType(const Tags *entity_tags) noexcept;

 private:
  /// @brief Map of enemy type strings to their respective types
  static inline std::map<std::string, sdk::game::types::EnemyType> kEnemyTypeMap_ = {
      {"pata", sdk::game::types::EnemyType::kPata},
      {"pata_big", sdk::game::types::EnemyType::kPataBig},
      {"grappler", sdk::game::types::EnemyType::kGrappler},
  };

  /// @brief Map of bullet type strings to their respective types
  static inline std::map<std::string, sdk::game::types::ProjectileType> kProjectileTypeMap_ = {
      {"player_bullet", sdk::game::types::ProjectileType::kPlayerCommon},
      {"pata_bullet", sdk::game::types::ProjectileType::kPata},
      {"grappler_bullet", sdk::game::types::ProjectileType::kGrappler},
  };
};
}  // namespace rtype::server::game::network
