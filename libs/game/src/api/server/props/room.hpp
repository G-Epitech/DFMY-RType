/*
** EPITECH PROJECT, 2024
** room.hpp
** File description:
** room class
*/

#pragma once

#include <cstdint>
#include <string>

namespace rtype::sdk::game::api {
struct RoomProps {
  std::uint64_t id;
  std::string name;
  unsigned int maxPlayers;
  unsigned int nbPlayers;
  unsigned int difficulty;
  unsigned int gamePort;
  unsigned int chatPort;
};
}  // namespace rtype::sdk::game::api
