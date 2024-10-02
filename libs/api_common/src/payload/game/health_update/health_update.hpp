/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** currentHealth.hpp
*/

#pragma once

#include <cstddef>

#include "libs/api_common/src/api.hpp"

namespace rtype::sdk::api_common::payload {
/// @brief Health update
struct EXPORT_API_COMMON_SDK_API HealthUpdate {
  /// @brief The entity id
  std::size_t entityId;
  /// @brief The current health of the entity
  std::size_t currentHealth;

  /**
   * @brief Construct a new Health Update object
   * @param entityId Entity id
   * @param currentHealth Current health
   */
  HealthUpdate(std::size_t entityId, std::size_t currentHealth);
};
}  // namespace rtype::sdk::api_common
