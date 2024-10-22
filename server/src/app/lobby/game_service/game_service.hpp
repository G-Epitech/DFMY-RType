/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** GameService.hpp
*/

#pragma once

#include <cstddef>
#include <map>

#include "enemy_manager/enemy_manager.hpp"
#include "libs/game/includes/api.hpp"
#include "registry.hpp"
#include "ticks/ticks_manager.hpp"
#include "zygarde/src/utils/helper/helper.hpp"
#include "zygarde/src/utils/timer/timer.hpp"

namespace rtype::server::game {
class GameService {
 public:
  /**
   * @brief Construct a new Game Service object
   * @param tick_rate The tick rate of the game
   */
  explicit GameService(const std::size_t &tick_rate);

  ~GameService() = default;

 public:
  /**
   * @brief Run the game service
   * @return Status code
   */
  int Run(uint64_t lobbyId, std::shared_ptr<rtype::sdk::game::api::Server> api);

  /**
   * @brief Add a new player to the game
   * @param playerId The player id
   */
  void NewPlayer(std::uint64_t playerId);

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
   * @brief Handle messages from the server
   */
  void HandleMessages();

  /**
   * @brief Send stats to the server
   */
  void SendStates();

 private:
  /// @brief Game running flag
  bool gameRunning_{true};
  /// @brief Ticks manager for the game
  TicksManager ticksManager_;
  /// @brief Registry containing all entities
  std::shared_ptr<zygarde::Registry> registry_;
  /// @brief Enemy manager
  EnemyManager enemyManager_;
  /// @brief Server network
  std::shared_ptr<rtype::sdk::game::api::Server> api_;
  /// @brief Lobby id
  uint64_t lobbyId_;
  /// @brief Player list
  std::map<std::uint64_t, zygarde::Entity> players_;
  /// @brief Packet builder
  abra::tools::PacketBuilder packetBuilder_;
  /// @brief Logger
  abra::tools::Logger logger_;
};
}  // namespace rtype::server::game
