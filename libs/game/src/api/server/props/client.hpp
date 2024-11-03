/*
** EPITECH PROJECT, 2024
** client.hpp
** File description:
** client class
*/

#pragma once

#include <cstdint>
#include <string>

namespace rtype::sdk::game::api {
struct ClientProps {
  std::uint64_t id;
  std::string username;
  bool inRoom;
  std::uint64_t nodeId;
  std::uint64_t roomId;
};
}  // namespace rtype::sdk::game::api
