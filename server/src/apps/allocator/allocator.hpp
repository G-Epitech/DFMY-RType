/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** allocator.hpp
*/

#pragma once

#include <cstddef>

#include "props.hpp"
#include "src/apps/context.hpp"
#include "src/apps/server_interface.hpp"

namespace rtype::server {

class Allocator final : public IServer {
 public:
  explicit Allocator(const BaseContext &ctx);
  ~Allocator() override = default;

  int Run() override;

 private:
  struct Context {
    std::string name;  // Name of the server context
    std::size_t port;  // Port number
    ServerType type;   // Server type
    AllocatorCtxProps props;
  };

 private:
  Context mCtx;
};
}  // namespace rtype::server
