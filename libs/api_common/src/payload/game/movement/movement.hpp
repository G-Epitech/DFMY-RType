/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** movement.hpp
*/

#pragma once

#include <cstddef>

#include "libs/api_common/src/api.hpp"
#include "libs/utils/src/types/vector/vector_2f.hpp"

using namespace rtype::sdk;

namespace rtype::sdk::api_common::payload {
/// @brief Movement payload
struct EXPORT_API_COMMON_SDK_API Movement {
  /// @brief The entity id
  std::size_t entityId;
  /// @brief The new position
  utils::types::vector_2f newPosition;

  /**
   * @brief Construct a new Movement object
   * @param entityId Id of the entity
   * @param newPosition New position of the entity
   */
  Movement(std::size_t entityId, utils::types::vector_2f newPosition);
};
}  // namespace rtype::sdk::api_common::payload
