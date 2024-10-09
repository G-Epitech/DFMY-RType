/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** TicksManager.hpp
*/

#pragma once

#include <cstddef>

#include "zygarde/src/utils/timer/timer.hpp"

namespace rtype::server::game {
class TicksManager {
 public:
  explicit TicksManager(const std::size_t &tickRate);
  ~TicksManager() = default;

  inline void Update() { timer_.Update(); }

  inline void Initialize() { timer_.Initialize(); }

  [[nodiscard]] inline const zygarde::utils::Timer::Nanoseconds &DeltaTime() {
    return timer_.GetDeltaTime();
  }

  void WaitUntilNextTick();

 private:
  const std::size_t &tickRate_;
  std::chrono::milliseconds millisecondsPerTick_;
  zygarde::utils::Timer timer_;
};
}  // namespace rtype::server::game
