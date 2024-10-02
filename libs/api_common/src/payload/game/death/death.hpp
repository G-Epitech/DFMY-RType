/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** death.hpp
*/

#pragma once

#include <cstddef>

#include "libs/api_common/src/api.hpp"

namespace rtype::sdk::api_common::payload {
/// @brief Death of an entity
struct EXPORT_API_COMMON_SDK_API Death {
  /// @brief Entity id
  std::size_t entityId;

  /**
   * @brief Construct a new Death object
   * @param entityId Entity id
   */
  explicit Death(std::size_t entityId);
};
}  // namespace rtype::sdk::api_common::payload
