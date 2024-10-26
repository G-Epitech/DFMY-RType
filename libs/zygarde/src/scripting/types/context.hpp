/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** context.hpp
*/

#pragma once

#include "registry.hpp"
#include "utils/timer/timer.hpp"

namespace zygarde::scripting::types {
using ValuesMap = std::map<std::string, std::any>;

struct ScriptingContext {
  using Ptr = std::shared_ptr<ScriptingContext>;
  using ConstPtr = const std::shared_ptr<ScriptingContext> &;

  const Registry::Ptr &registry;
  const utils::Timer::Nanoseconds &deltaTime;
  zygarde::Entity me;
};
}  // namespace zygarde::scripting::types
