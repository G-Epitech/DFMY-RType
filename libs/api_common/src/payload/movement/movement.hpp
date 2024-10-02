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
struct EXPORT_API_COMMON_SDK_API Movement {
  std::size_t entityId{0};
  utils::types::vector_2f newPosition;

  Movement(std::size_t entityId, utils::types::vector_2f newPosition);
};
}  // namespace rtype::sdk::api_common::payload
