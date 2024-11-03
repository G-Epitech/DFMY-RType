/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** player_props.hpp
*/

#pragma once

#include "zygarde/src/entity.hpp"

namespace rtype::server::game {
struct PlayerProps {
  zygarde::Entity entity;
  int score;
};
}  // namespace rtype::server::game
