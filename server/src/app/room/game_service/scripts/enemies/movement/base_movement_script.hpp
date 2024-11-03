/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** base_movement_script.hpp
*/

#pragma once

#include "zygarde/src/scripting/components/mono_behaviour/mono_behaviour.hpp"

namespace rtype::server::game::scripts {
class BaseMovementScript : public zygarde::scripting::components::MonoBehaviour {
 public:
  /**
   * @brief Set the base position for the movement
   * @param basePosition The base position
   */
  inline void SetBasePosition(const zygarde::core::types::Vector3f& basePosition) {
    basePosition_ = basePosition;
  }

 protected:
  zygarde::core::types::Vector3f basePosition_{0.0f, 0.0f, 0.0f};
};
}  // namespace rtype::server::game::scripts
