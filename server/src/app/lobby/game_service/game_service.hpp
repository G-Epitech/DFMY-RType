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
  explicit GameService(const std::size_t &tick_rate);
  ~GameService() = default;

  void Run();

 private:
  void ExecuteGameLogic() const;

  void Initialize();

  void RegistrySetup();

 private:
  bool gameRunning_{true};
  TicksManager ticksManager_;
  std::shared_ptr<zygarde::Registry> registry_;
};
}  // namespace rtype::server::game
