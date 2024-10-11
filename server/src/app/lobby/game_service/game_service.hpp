/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** GameService.hpp
*/

#pragma once

#include <cstddef>

#include "registry.hpp"
#include "ticks/ticks_manager.hpp"
#include "zygarde/src/utils/registry_helper/registry_helper.hpp"
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
  int Run();

 private:
  /**
   * @brief Execute the game logic during a tick
   */
  void ExecuteGameLogic() const;

  /**
   * @brief Initialize the game service
   */
  void Initialize();

  /**
   * @brief Setup the registry
   */
  void RegistrySetup();

 private:
  /// @brief Game running flag
  bool gameRunning_{true};
  /// @brief Ticks manager for the game
  TicksManager ticksManager_;
  /// @brief Registry containing all entities
  std::shared_ptr<zygarde::Registry> registry_;
};
}  // namespace rtype::server::game
