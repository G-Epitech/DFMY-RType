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
  const Registry::Ptr &registry;
  ValuesMap &values;
  const utils::Timer::Nanoseconds &deltaTime;
};
}  // namespace zygarde::scripting::types
