/*
** EPITECH PROJECT, 2024
** scores.hpp
** File description:
** scores header
*/

#pragma once

#include <cstdint>
#include <string>

namespace rtype::sdk::game::api::schema {
/// @brief The score schema
struct Score {
  std::int64_t id = 0;   ///< @brief The score id
  std::string roomName;  ///< @brief The room name
  std::int64_t score;    ///< @brief The score
  bool win;              ///< @brief The win status
};
}  // namespace rtype::sdk::game::api::schema
