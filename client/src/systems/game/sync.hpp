/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** sync.hpp
*/

#pragma once

#include <map>
#include <set>

#include "client/src/services/server_connection_service.hpp"
#include "components/server_entity_id.hpp"
#include "core/types/vector/vector_2f.hpp"
#include "libs/zygarde/src/system_abstract.hpp"
#include "managers/settings_manager.hpp"

#define PLAYER_KINEMATIC false
#define PLAYER_DRAG 5.0f
#define ENEMY_KINEMATIC false
#define ENEMY_DRAG 0.0f
#define BULLET_KINEMATIC true
#define BULLET_DRAG 0.0f

namespace rtype::client::systems {
class GameSyncSystem final : public ASystem<> {
 public:
  /**
   * @brief Construct a new Game Sync System object
   * @param server_connection_service Pointer to the server connection service
   * @param settingsManager Pointer to the settings manager
   */
  explicit GameSyncSystem(services::ServerConnectionService::Ptr server_connection_service,
                          mew::managers::SettingsManager::Ptr settingsManager);

  void Run(Registry::Ptr r) override;

 private:
  /// @brief Server connection service
  services::ServerConnectionService::Ptr serverConnectionService_;

  /// @brief Settings manager
  mew::managers::SettingsManager::Ptr settingsManager_;

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
   * @param state State of the player
   */
  void CreatePlayer(const std::shared_ptr<Registry> &registry,
                    const api::payload::PlayerState &state);

  /**
   * @brief Update a player
   * @param registry The registry
   * @param state State of the player
   */
  void UpdatePlayer(const std::shared_ptr<Registry> &registry,
                    const api::payload::PlayerState &state);

  /**
   * @brief Create a bullet
   * @param registry The registry
   * @param state State of the bullet
   */
  void CreateBullet(const std::shared_ptr<Registry> &registry,
                    const sdk::game::api::payload::BulletState &state);

  /**
   * @brief Update a bullet
   * @param registry The registry
   * @param state State of the bullet
   */
  void UpdateBullet(const std::shared_ptr<Registry> &registry,
                    const api::payload::BulletState &state);

  /**
   * @brief Create an enemy
   * @param registry The registry
   * @param state State of the enemy
   */
  void CreateEnemy(const std::shared_ptr<Registry> &registry,
                   const api::payload::EnemyState &state);

  /**
   * @brief Update an enemy
   * @param registry The registry
   * @param state State of the enemy
   */
  void UpdateEnemy(const std::shared_ptr<Registry> &registry,
                   const api::payload::EnemyState &state);

  /**
   * @brief Handle a message from the server
   * @param registry The registry
   * @param message Message from the server
   */
  void HandleMessage(const Registry::Ptr &registry, const api::Client::ServerMessage &message);

  /**
   * @brief Handle the players message
   * @param registry The registry
   * @param message Message to handle
   */
  void HandlePlayers(const Registry::Ptr &registry, const api::Client::ServerMessage &message);

  /**
   * @brief Handle the end gale message
   * @param registry The registry
   * @param message Message to handle
   */
  void HandleGameEnded(const Registry::Ptr &registry, const api::Client::ServerMessage &message);

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
