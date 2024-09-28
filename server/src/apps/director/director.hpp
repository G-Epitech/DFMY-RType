/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** director.hpp
*/

#pragma once

#include <cstddef>

#include "props.hpp"
#include "src/apps/context.hpp"
#include "src/apps/server_interface.hpp"

namespace rtype::server {

class Director final : public IServer {
 public:
  explicit Director(const BaseContext &ctx);
  ~Director() override = default;

  int Run() override;

 private:
  struct Context {
    std::string name;  // Name of the server context
    std::size_t port;  // Port number
    ServerType type;   // Server type
    DirectorCtxProps props;
  };

 private:
  Context mCtx;
};
}  // namespace rtype::server
