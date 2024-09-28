/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** server_interface.hpp
*/

#pragma once

namespace rtype::server {
class IServer {
 public:
  virtual ~IServer() = default;

  virtual int Run() = 0;
};
}  // namespace rtype::server
