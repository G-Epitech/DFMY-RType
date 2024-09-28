/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** props.hpp
*/

#pragma once

#include <utility>

namespace rtype::server {
struct LobbyCtxProps {
  std::size_t ticks;

  explicit LobbyCtxProps(std::size_t ticks) : ticks(ticks) {}

  LobbyCtxProps() : ticks(0) {}
};
}  // namespace rtype::server
