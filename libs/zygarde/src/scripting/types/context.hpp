/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** context.hpp
*/

#pragma once

#include "registry.hpp"

namespace zygarde::scripting::types {
using ValuesMap = std::map<std::string, std::any>;

struct ScriptingContext {
  const Registry::Ptr &registry;
  const ValuesMap &values;
};
}  // namespace zygarde::scripting::types
