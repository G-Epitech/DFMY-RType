/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** fire_rate.cpp
*/

#include "fire_rate.hpp"

namespace rtype::sdk::game::utils {
EXPORT_GAME_SDK_API std::chrono::nanoseconds GetFireRate(const float &fire_rate) {
  return std::chrono::nanoseconds(
      static_cast<std::chrono::nanoseconds::rep>(static_cast<float>(1000000000) / fire_rate));
};
}  // namespace rtype::sdk::game::utils
