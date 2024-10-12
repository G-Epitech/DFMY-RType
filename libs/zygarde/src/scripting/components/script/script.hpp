/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Script.hpp
*/

#pragma once

#include "api.hpp"
#include "scripting/types/callbacks.hpp"

namespace zygarde::scripting::components {
class EXPORT_ZYGARDE_API Script final {
 public:
  Script() = default;
  ~Script() = default;

  Script(types::Collision2DFunction on_collision_enter, types::FixedUpdateFunction fixed_update,
         types::ValuesMap values);

  Script(types::Collision2DFunction on_collision_enter, types::FixedUpdateFunction fixed_update);

 public:
  /**
   * @brief Set a value in the script
   * @param key Key of the value
   * @param value Value to set
   */
  inline void SetValue(const std::string &key, const std::any &value) noexcept {
    values_[key] = value;
  }

 public:
  std::optional<types::Collision2DFunction> onCollisionEnter;
  std::optional<types::FixedUpdateFunction> fixedUpdate;

 private:
  types::ValuesMap values_;
};
}  // namespace zygarde::scripting::components
