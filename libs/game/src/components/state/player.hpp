/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** player_state.hpp
*/

#pragma once

namespace rtype::sdk::game::components {
struct PlayerStateComponent {
  bool damaged;
  bool dead;
  bool poweredUp;
};
}  // namespace rtype::sdk::game::components
