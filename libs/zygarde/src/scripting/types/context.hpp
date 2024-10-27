/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** context.hpp
*/

#pragma once

#include "core/archetypes/archetype_manager.hpp"
#include "registry.hpp"
#include "utils/timer/timer.hpp"

namespace zygarde::scripting::types {
struct ScriptingContext {
  using Ptr = std::shared_ptr<ScriptingContext>;
  using ConstPtr = const std::shared_ptr<ScriptingContext> &;

  const Registry::Ptr &registry;
  const utils::Timer::Nanoseconds &deltaTime;
  zygarde::Entity me;
  const std::shared_ptr<zygarde::core::archetypes::ArchetypeManager> &archetypeManager;
};
}  // namespace zygarde::scripting::types
