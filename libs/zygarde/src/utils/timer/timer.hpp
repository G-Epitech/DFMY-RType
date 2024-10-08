/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Timer.hpp
*/

#pragma once

#include <chrono>

#include "libs/zygarde/src/api.hpp"

namespace zygarde::utils {
class EXPORT_ZYGARDE_API Timer final {
 public:
  using Nanoseconds = std::chrono::nanoseconds;
  using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

 public:
  Timer() = default;
  ~Timer() = default;

 public:
  /**
   * @brief Update the timer
   * This should be called at the beginning of the game loop
   * to update the delta time and the current time point
   */
  void Update() noexcept;

  /**
   * @brief Initialize the timer
   * This should be called before the game loop
   * to initialize the previous time point
   */
  void Initialize() noexcept;

  /**
   * @brief Get the delta time in Nanoseconds
   */
  [[nodiscard]] inline Nanoseconds GetDeltaTime() const noexcept { return deltaTime_; };

  /**
   * @brief Convert Nanoseconds to Seconds
   * @return Seconds
   */
  static double ToSeconds(Nanoseconds nanoseconds) noexcept;

  /**
   * @brief Get the current time point
   */
  static TimePoint Now() noexcept;

 private:
  /// @brief Delta time representing the time between the current and previous time point
  Nanoseconds deltaTime_ = Nanoseconds(0);
  /// @brief Previous time point
  TimePoint lastTimePoint_ = Now();
};
}  // namespace zygarde::utils
