/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** args_server_type.hpp
*/

#pragma once

#include <boost/program_options.hpp>
#include <stdexcept>
#include <vector>

#include "server/src/server_types.hpp"

namespace rtype::server {
inline ServerType StringToServerType(const std::string& value) {
  if (value == "allocator")
    return ServerType::kAllocator;
  if (value == "lobby")
    return ServerType::kLobby;
  throw std::invalid_argument("Invalid server type: " + value);
}

inline void validate(boost::any& v, const std::vector<std::string>& values, ServerType*, int) {
  if (values.size() != 1)
    throw std::runtime_error("ServerType expects a single value");

  const std::string& value = values[0];
  v = boost::any(StringToServerType(value));
}
}  // namespace rtype::server
