/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** newHp.hpp
*/

#pragma once

#include <cstddef>

#include "libs/api_common/src/api.hpp"

namespace rtype::sdk::api_common::payload {
struct EXPORT_API_COMMON_SDK_API DamageDealt {
  std::size_t entityId;
  std::size_t newHp;

  DamageDealt(std::size_t entityId, std::size_t newHp);
};
}  // namespace rtype::sdk::api_common
