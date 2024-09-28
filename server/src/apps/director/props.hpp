/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** props.hpp
*/

#pragma once

#include <utility>

namespace rtype::server {
struct DirectorCtxProps {
  std::size_t maxGames;
  std::size_t ticks;

  DirectorCtxProps(std::size_t maxGames, std::size_t ticks) : maxGames(maxGames), ticks(ticks) {}

  DirectorCtxProps() : maxGames(0), ticks(0) {}
};
}  // namespace rtype::server
