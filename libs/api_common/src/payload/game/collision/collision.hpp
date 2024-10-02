/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** collision.hpp
*/

#pragma once

#include <cstddef>

#include "libs/api_common/src/api.hpp"

namespace rtype::sdk::api_common::payload {
/// @brief Collision between two entities
struct EXPORT_API_COMMON_SDK_API Collision {
  /// @brief The first entity id
  std::size_t entityId1;
  /// @brief The second entity id
  std::size_t entityId2;

  /**
   * @brief Construct a new Collision object
   * @param entityId1 the first entity id
   * @param entityId2 the second entity id
   */
  Collision(std::size_t entityId1, std::size_t entityId2);
};
}  // namespace rtype::sdk::api_common::payload
