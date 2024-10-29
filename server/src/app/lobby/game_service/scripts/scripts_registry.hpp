/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** scripts_registry.hpp
*/

#pragma once

#include <unordered_map>

#include "zygarde/src/scripting/components/mono_behaviour/mono_behaviour.hpp"
#include "zygarde/src/scripting/types/mono_behaviour.hpp"

namespace rtype::server::game::scripts {
/**
 * @brief Scripts registry class, mainly used for the archetype manager.
 * Will later be changed when lua bindings are implemented
 */
class ScriptsRegistry {
 public:
  ScriptsRegistry();
  ~ScriptsRegistry() = default;

  /**
   * @brief Get a script by name
   * @param name Script name
   * @return Script shared pointer
   */
  scripting::components::MonoBehaviour::Instance GetScript(const std::string& name);

  /**
   * @brief Get all scripts of the registry
   * @return Scripts map
   */
  [[nodiscard]] const zygarde::scripting::types::ScriptsMap& GetScripts() const { return scripts_; }

 private:
  /// @brief Scripts map
  zygarde::scripting::types::ScriptsMap scripts_;
};
}  // namespace rtype::server::game::scripts
