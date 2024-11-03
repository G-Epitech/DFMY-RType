/*
** EPITECH PROJECT, 2024
** node.hpp
** File description:
** node class
*/

#pragma once

#include <cstdint>
#include <map>
#include <string>

#include "./room.hpp"

namespace rtype::sdk::game::api {
struct NodeProps {
  std::uint64_t id;
  std::string name;
  std::size_t maxRooms;
  std::map<std::uint64_t, RoomProps> rooms_;
};
}  // namespace rtype::sdk::game::api
