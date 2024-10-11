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
  /**
   * @brief Register base components available by default in the zygarde engine
   * @param registry The registry you want to register the components to
   */
  static void RegisterBaseComponents(Registry* registry);

  /**
   * @brief Register base systems available by default in the zygarde engine
   * @param registry The registry you want to register the systems to
   * @param delta_time Reference to the delta time
   */
  static void RegisterBaseSystems(Registry* registry, const utils::Timer::Nanoseconds& delta_time);

 private:
  /**
   * @brief Register core components available by default in the zygarde engine
   * @param registry The registry you want to register the components to
   */
  static void RegisterCoreComponents(Registry* registry);

  /**
   * @brief Register physics components available by default in the zygarde engine
   * @param registry The registry you want to register the components to
   */
  static void RegisterPhysicsComponents(Registry* registry);

  /**
   * @brief Register physics systems available by default in the zygarde engine
   * @param registry The registry you want to register the systems to
   * @param delta_time Reference to the delta time
   */
  static void RegisterPhysicsSystems(Registry* registry,
                                     const utils::Timer::Nanoseconds& delta_time);
};
}  // namespace zygarde::utils
