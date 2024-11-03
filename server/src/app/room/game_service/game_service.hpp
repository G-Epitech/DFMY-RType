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
#include "types/player_props.hpp"
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

  /**
   * @brief Get the number of players
   * @return The number of players
   */
  std::size_t GetNbPlayers() const;

  /**
   * @brief Initialize the game service
   */
  int Initialize();

 private:
  /**
   * @brief Execute the game logic during a tick
   */
  void ExecuteGameLogic();

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

  /**
   * @brief Update the player scores
   */
  void UpdatePlayerScores();

  /**
   * @brief Handle the game end
   */
  void HandleGameEnd();

  /**
   * @brief Check if the game has ended
   */
  void CheckGameEnd();

  /**
   * @brief Compute the total score of the game
   * @return The total score
   */
  [[nodiscard]] unsigned int ComputeTotalScore() const;

  /**
   * @brief Check if entities are too far and kill them if they are
   */
  void CheckTooFarEntities();

  /**
   * @brief Start game clock
   */
  inline void StartGameClock() { startTime_ = std::chrono::steady_clock::now(); }

  /**
   * @brief Update total game time
   */
  void GetTotalGameTime();

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
  std::map<std::uint64_t, PlayerProps> players_;

  /// @brief Dead player list
  std::list<std::pair<std::uint64_t, PlayerProps>> deadPlayers_;

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

  /// @brief Difficulty of the game
  std::size_t difficulty_;

  /// @brief Player counter
  std::size_t playerCounter_;

  /// @brief Win flag
  bool win_{false};

  /// @brief Total time of the game
  time_t totalGameTime_{0};

  /// @brief Total score of the game
  int scorePenalty_{0};

  /// @brief Start time of the game
  std::chrono::steady_clock::time_point startTime_;
};
}  // namespace rtype::server::game
