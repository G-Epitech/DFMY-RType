/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** RegistryHelper.hpp
*/

#pragma once

#include <memory>

#include "api.hpp"
#include "core/components/components.hpp"
#include "physics/2d/components/components.hpp"
#include "physics/2d/systems/systems.hpp"
#include "registry.hpp"
#include "utils/timer/timer.hpp"

namespace zygarde::utils {
class EXPORT_ZYGARDE_API RegistryHelper final {
 public:
  RegistryHelper() = delete;
  ~RegistryHelper() = default;

 public:
  static void RegisterBaseComponents(Registry* registry);
  static void RegisterBaseSystems(Registry* registry, const utils::Timer::Nanoseconds& deltaTime);

 private:
  static void RegisterCoreComponents(Registry* registry);
  static void RegisterPhysicsComponents(Registry* registry);

  static void RegisterPhysicsSystems(Registry* registry,
                                     const utils::Timer::Nanoseconds& deltaTime);
};
}  // namespace zygarde::utils
