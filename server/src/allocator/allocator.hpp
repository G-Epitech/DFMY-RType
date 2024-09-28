/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** allocator.hpp
*/

#pragma once

#include <cstddef>

#include "props.hpp"
#include "src/context.hpp"

namespace rtype::server {

class Allocator {
 public:
  explicit Allocator(const BaseContext &ctx);
  ~Allocator() = default;

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
