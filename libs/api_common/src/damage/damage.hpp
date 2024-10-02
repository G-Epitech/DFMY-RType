/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** damage.hpp
*/

#pragma once

#include <cstddef>

#include "libs/api_common/src/api.hpp"

namespace rtype::sdk::api_common {
struct EXPORT_API_COMMON_SDK_API DamageDealt {
  std::size_t entityId;
  std::size_t damage;

  DamageDealt(std::size_t entityId, std::size_t damage);
};
}  // namespace rtype::sdk::api_common
