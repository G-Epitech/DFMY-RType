/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** enemy_spawned.hpp
*/

#pragma once

#include <cstddef>

#include "libs/api_common/src/api.hpp"
#include "libs/utils/src/types/vector/vector_2f.hpp"

namespace rtype::sdk::api_common::payload {
struct EXPORT_API_COMMON_SDK_API EnemySpawned {
  std::size_t entityId{0};
  utils::types::vector_2f position;

  EnemySpawned(std::size_t entityId, utils::types::vector_2f position);
};
}  // namespace rtype::sdk::api_common::payload
