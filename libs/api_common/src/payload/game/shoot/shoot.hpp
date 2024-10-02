/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** shoot.hpp
*/

#pragma once

#include <cstddef>

#include "libs/api_common/src/api.hpp"

namespace rtype::sdk::api_common::payload {
/// @brief Shoot payload
struct EXPORT_API_COMMON_SDK_API Shoot {
  /// @brief Entity id
  std::size_t entityId{0};

  /**
   * @brief Construct a new Shoot object
   * @param entityId Entity id
   */
  explicit Shoot(std::size_t entityId);
};
}  // namespace rtype::sdk::api_common::payload
