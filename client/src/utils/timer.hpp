/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** timer.hpp
*/

#pragma once
#include <chrono>

#include "time.hpp"
namespace rtype::client::utils {
struct Timer {
  /**
   * @brief Construct a new Timer object
   */
  Timer();

  /**
   * @brief Process a tick
   */
  void tick();

  /**
   * @brief Get the elapsed time since the last tick
   * @return The elapsed time
   */
  [[nodiscard]] DeltaTime GetElapsedTime() const;

 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> _last;
};
}  // namespace rtype::client::utils
