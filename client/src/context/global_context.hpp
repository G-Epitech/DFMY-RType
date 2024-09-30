/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** global_context.hpp
*/

#pragma once

#include <memory>

namespace rtype::client {
struct GlobalContext {
  using Ptr = std::shared_ptr<GlobalContext>;
  int superGlobalVar = 42;
};
}  // namespace rtype::client
