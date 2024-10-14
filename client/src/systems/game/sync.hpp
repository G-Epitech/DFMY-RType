/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** sync.hpp
*/

#pragma once

#include <map>
#include <set>

#include "components/server_entity_id.hpp"
#include "core/types/vector/vector_2f.hpp"
#include "libs/zygarde/src/system_abstract.hpp"
#include "managers/server_connection_manager.hpp"

namespace rtype::client::systems {
class GameSyncSystem final : public ASystem<components::ServerEntityId> {
 public:
  /**
   * @brief Construct a new Game Sync System object
   * @param serverConnectionManager Pointer to the server connection manager
   */
  explicit GameSyncSystem(ServerConnectionManager::Ptr serverConnectionManager);

  void Run(Registry::Ptr r, sparse_array<components::ServerEntityId>::ptr component) override;

 private:
  /**
   * @brief Pointer to the server connection manager
   */
  ServerConnectionManager::Ptr serverConnectionManager_;

  /**
   * @brief Players list
   */
  std::map<std::size_t, Entity> players_;

  /**
   * @brief Bullets list
   */
  std::map<std::size_t, Entity> bullets_;

  /**
   * @brief Enemies list
   */
  std::map<std::size_t, Entity> enemies_;

  /**
   * @brief Create a player
   * @param registry The registry
   * @param id The id of the player
   * @param pos The position of the player
   */
  void CreatePlayer(const std::shared_ptr<Registry> &registry, const std::size_t &id,
                    const zygarde::core::types::Vector3f &pos);
  /**
   * @brief Update a player
   * @param registry The registry
   * @param id Id of the player
   * @param pos Position of the player
   */
  void UpdatePlayer(const std::shared_ptr<Registry> &registry, const std::size_t &id,
                    const zygarde::core::types::Vector3f &pos);

  /**
   * @brief Create a bullet
   * @param registry The registry
   * @param id The id of the bullet
   * @param pos The position of the bullet
   */
  void CreateBullet(const std::shared_ptr<Registry> &registry, const std::size_t &id,
                    const zygarde::core::types::Vector3f &pos);

  /**
   * @brief Update a bullet
   * @param registry The registry
   * @param id Id of the bullet
   * @param pos Position of the bullet
   */
  void UpdateBullet(const std::shared_ptr<Registry> &registry, const std::size_t &id,
                    const zygarde::core::types::Vector3f &pos);

  /**
   * @brief Create an enemy
   * @param registry The registry
   * @param id The id of the enemy
   * @param pos The position of the enemy
   */
  void CreateEnemy(const std::shared_ptr<Registry> &registry, const std::size_t &id,
                   const zygarde::core::types::Vector3f &pos);

  /**
   * @brief Update an enemy
   * @param registry The registry
   * @param id Id of the enemy
   * @param pos Position of the enemy
   */
  void UpdateEnemy(const std::shared_ptr<Registry> &registry, const std::size_t &id,
                   const zygarde::core::types::Vector3f &pos);

  /**
   * @brief Handle a message from the server
   * @param registry The registry
   * @param message Message from the server
   * @param handled Set of handled entities
   */
  void HandleMessage(const Registry::Ptr &registry, const api::Client::ServerMessage &message);

  /**
   * @brief Handle the players message
   * @param registry The registry
   * @param message Message to handle
   */
  void HandlePlayers(const Registry::Ptr &registry, const api::Client::ServerMessage &message);

  /**
   * @brief Handle the player state
   * @param registry The registry
   * @param state State of the player
   * @param handled Set of handled entities
   */
  void HandlePlayerState(const Registry::Ptr &registry, const api::payload::PlayerState &state,
                         std::set<std::size_t> *handled);

  /**
   * @brief Handle the bullets message
   * @param registry The registry
   * @param message Message to handle
   */
  void HandleBullets(const Registry::Ptr &registry, const api::Client::ServerMessage &message);

  /**
   * @brief Handle the bullet state
   * @param registry The registry
   * @param state State of the bullet
   * @param handled Set of handled entities
   */
  void HandleBulletState(const Registry::Ptr &registry, const api::payload::BulletState &state,
                         std::set<std::size_t> *handled);

  /**
   * @brief Handle the enemies message
   * @param registry The registry
   * @param message Message to handle
   */
  void HandleEnemies(const Registry::Ptr &registry, const api::Client::ServerMessage &message);

  /**
   * @brief Handle the enemy state
   * @param registry The registry
   * @param state State of the enemy
   * @param handled Set of handled entities
   */
  void HandleEnemyState(const Registry::Ptr &registry, const api::payload::EnemyState &state,
                        std::set<std::size_t> *handled);

  /**
   * @brief Delete entities
   * @param registry The registry
   * @param handled Set of handled entities
   * @param entities Entities to delete
   */
  static void DeleteEntities(const Registry::Ptr &registry, const std::set<std::size_t> &handled,
                             std::map<std::size_t, Entity> *entities);
};
}  // namespace rtype::client::systems
