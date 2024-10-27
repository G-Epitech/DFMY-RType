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
class ScriptsRegistry {
 public:
  ScriptsRegistry();
  ~ScriptsRegistry() = default;

  scripting::components::MonoBehaviour::Instance GetScript(const std::string& name);

  [[nodiscard]] const zygarde::scripting::types::ScriptsMap& GetScripts() const { return scripts_; }

 private:
  zygarde::scripting::types::ScriptsMap scripts_;
};
}  // namespace rtype::server::game::scripts
