/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** scripts_registry.cpp
*/

#include "scripts_registry.hpp"

#include "enemies/pata_script.hpp"
#include "player_script.hpp"
#include "projectiles/base_projectile_script.hpp"

using namespace rtype::server::game::scripts;

ScriptsRegistry::ScriptsRegistry() : scripts_() {
  scripts_["playerScript"] = []() -> scripting::components::MonoBehaviour::Instance {
    return std::make_shared<PlayerScript>();
  };
  scripts_["baseProjectileScript"] = []() -> scripting::components::MonoBehaviour::Instance {
    return std::make_shared<BaseProjectileScript>();
  };
  scripts_["pataScript"] = []() -> scripting::components::MonoBehaviour::Instance {
    return std::make_shared<PataScript>();
  };
}

scripting::components::MonoBehaviour::Instance ScriptsRegistry::GetScript(const std::string& name) {
  if (scripts_.find(name) == scripts_.end()) {
    return nullptr;
  }
  return scripts_[name]();
}
