/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** GameService.hpp
*/

#pragma once

#include <cstddef>
#include <map>

#include "difficulty_loader/difficulty_loader.hpp"
#include "level_manager/level_manager.hpp"
#include "libs/game/includes/api.hpp"
#include "network/message_handler/message_handler.hpp"
#include "player_spawner/player_spawner.hpp"
#include "ticks/ticks_manager.hpp"
#include "zygarde/src/core/archetypes/archetype_manager.hpp"
#include "zygarde/src/registry.hpp"
#include "zygarde/src/utils/helper/helper.hpp"
#include "zygarde/src/utils/timer/timer.hpp"

namespace rtype::server::game {
class GameService {
 public:
  /**
   * @brief Construct a new Game Service object
   * @param tick_rate The tick rate of the game
   * @param difficulty The difficulty of the game
   */
  GameService(const std::size_t &tick_rate, std::size_t difficulty);

  ~GameService() = default;

 public:
  /**
   * @brief Run the game service
   * @return Status code
   */
  int Run(std::shared_ptr<rtype::sdk::game::api::Room> api);

  /**
   * @brief Add a new player to the game
   * @param player_id The player id
   */
  void NewPlayer(std::uint64_t player_id);

 private:
  /**
   * @brief Execute the game logic during a tick
   */
  void ExecuteGameLogic();

  /**
   * @brief Initialize the game service
   */
  void Initialize();

  /**
   * @brief Setup the registry
   */
  void RegistrySetup();

  /**
   * @brief Check if a player is dead
   */
  void CheckDeadPlayers();

  /**
   * @brief Add game walls
   */
  void AddGameWalls();

  /**
   * @brief Setup the level and difficulty
   */
  void LevelAndDifficultySetup();

 private:
  /// @brief Game running flag
  bool gameRunning_{true};

  /// @brief Ticks manager for the game
  TicksManager ticksManager_;

  /// @brief Registry containing all entities
  std::shared_ptr<zygarde::Registry> registry_;

  /// @brief Server network
  std::shared_ptr<rtype::sdk::game::api::Room> api_;

  /// @brief Player list
  std::map<std::uint64_t, zygarde::Entity> players_;

  /// @brief Packet builder
  abra::tools::PacketBuilder packetBuilder_;

  /// @brief Logger
  Logger logger_;

  /// @brief Archetype manager
  std::shared_ptr<zygarde::core::archetypes::ArchetypeManager> archetypeManager_;

  /// @brief Level manager
  LevelManager levelManager_;

  /// @brief DifficultyData loader
  DifficultyLoader difficultyLoader_;

  /// @brief Player spawner
  PlayerSpawner playerSpawner_;

  /// @brief Message handler
  network::MessageHandler messageHandler_;

  /// @brief
  std::size_t difficulty_;
};
}  // namespace rtype::server::game
