/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** GameService.hpp
*/

#pragma once

#include <cstddef>
#include <map>

#include "level_manager/level_manager.hpp"
#include "libs/game/includes/api.hpp"
#include "ticks/ticks_manager.hpp"
#include "zygarde/src/core/archetypes/archetype_manager.hpp"
#include "zygarde/src/utils/helper/helper.hpp"
#include "zygarde/src/utils/timer/timer.hpp"
#include "zygarde/src/registry.hpp"

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
   * @brief Handle messages from the server
   */
  void HandleMessages();

  /**
   * @brief Handle player message
   * @param player_id The player id of the message
   * @param data The message data
   */
  void HandlePlayerMessage(const std::uint64_t &player_id,
                           const abra::server::ClientUDPMessage &data);

  /**
   * @brief Handle player move message
   * @param player_id The player id
   * @param data The message data
   */
  void HandlePlayerMoveMessage(const std::uint64_t &player_id,
                               const abra::server::ClientUDPMessage &data);

  /**
   * @brief Handle player shoot message
   * @param player_id Player id
   * @param data The data of the message
   */
  void HandlePlayerShootMessage(const std::uint64_t &player_id,
                                const abra::server::ClientUDPMessage &data);

  /**
   * @brief Check if a player is dead
   */
  void CheckDeadPlayers();

  /**
   * @brief Add game walls
   */
  void AddGameWalls();

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
};
}  // namespace rtype::server::game
