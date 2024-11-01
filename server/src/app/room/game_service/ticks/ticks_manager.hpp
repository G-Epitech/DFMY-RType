/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** TicksManager.hpp
*/

#pragma once

#include <cstddef>

#include "libs/abra/src/tools/logger/logger.hpp"
#include "zygarde/src/utils/timer/timer.hpp"

namespace rtype::server::game {
class TicksManager {
 public:
  /**
   * @brief Construct a new Ticks Manager object
   * @param tick_rate The tick rate
   */
  explicit TicksManager(const std::size_t &tick_rate);
  ~TicksManager() = default;

 public:
  /**
   * @brief Update the tick manager values
   * @details This function updates time points as well as delta time
   */
  inline void Update() { timer_.Update(); }

  /**
   * @brief Initialize the values of the tick manager
   */
  inline void Initialize() { timer_.Initialize(); }

  /**
   * @brief Get the delta time
   * @return The delta time in Nanoseconds
   */
  [[nodiscard]] inline const zygarde::utils::Timer::Nanoseconds &DeltaTime() const noexcept {
    return timer_.GetDeltaTime();
  }

  /**
   * @brief Wait until the next tick
   * @details This function uses sleep_for to wait until the next tick depending on the tick rate
   */
  void WaitUntilNextTick();

  /**
   * @brief Log the wait time
   * @param wait_time The wait time
   */
  void LogWaitTime(int64_t wait_time);

 private:
  /// @brief The number of ticks per second
  const std::size_t &tickRate_;
  /// @brief The number of milliseconds that should be spent per tick
  std::chrono::milliseconds millisecondsPerTick_;
  /// @brief Timer for the ticks manager
  zygarde::utils::Timer timer_;
  /// @brief Logger
  abra::tools::Logger logger_;
};
}  // namespace rtype::server::game
