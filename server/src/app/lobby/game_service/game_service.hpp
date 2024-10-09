/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** GameService.hpp
*/

#pragma once

#include <cstddef>

#include "ticks/ticks_manager.hpp"
#include "zygarde/src/utils/timer/timer.hpp"

namespace rtype::server::game {
class GameService {
 public:
  explicit GameService(const std::size_t &tick_rate);
  ~GameService() = default;

  void Run();

 private:
  void ExecuteGameLogic() const;

 private:
  bool gameRunning_{true};
  TicksManager ticksManager_;
};
}  // namespace rtype::server::game
