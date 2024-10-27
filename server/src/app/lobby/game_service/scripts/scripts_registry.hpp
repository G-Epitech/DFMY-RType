/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** scripts_registry.hpp
*/

#pragma once

#include <unordered_map>

#include "zygarde/src/scripting/components/mono_behaviour/mono_behaviour.hpp"

namespace rtype::server::game::scripts {
class ScriptsRegistry {
 public:
  using MonoBehaviourCreater = std::function<scripting::components::MonoBehaviour::Instance()>;
  using ScriptsMap = std::unordered_map<std::string, MonoBehaviourCreater>;

 public:
  ScriptsRegistry();
  ~ScriptsRegistry() = default;

  scripting::components::MonoBehaviour::Instance GetScript(const std::string &name);

 private:
  ScriptsMap scripts_;
};
}  // namespace rtype::server::game::scripts
