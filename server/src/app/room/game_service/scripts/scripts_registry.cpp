/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** scripts_registry.cpp
*/

#include "scripts_registry.hpp"

#include "enemies/enemy_default_script.hpp"
#include "player_script.hpp"
#include "projectiles/default_projectile_script.hpp"
#include "scripts/enemies/movement/shark_movement_script.hpp"
#include "scripts/enemies/movement/straight_movement_script.hpp"
#include "scripts/enemies/movement/zigzag_movement_script.hpp"
#include "scripts/enemies/void_eater_script.hpp"

using namespace rtype::server::game::scripts;

ScriptsRegistry::ScriptsRegistry() : scripts_() {
  scripts_["playerScript"] = []() -> scripting::components::MonoBehaviour::Instance {
    return std::make_shared<PlayerScript>();
  };
  scripts_["baseProjectileScript"] = []() -> scripting::components::MonoBehaviour::Instance {
    return std::make_shared<DefaultProjectileScript>();
  };
  scripts_["enemyDefaultScript"] = []() -> scripting::components::MonoBehaviour::Instance {
    return std::make_shared<EnemyDefaultScript>();
  };
  scripts_["zigzagMovementScript"] = []() -> scripting::components::MonoBehaviour::Instance {
    return std::make_shared<ZigZagMovementScript>();
  };
  scripts_["straightMovementScript"] = []() -> scripting::components::MonoBehaviour::Instance {
    return std::make_shared<StraightMovementScript>();
  };
  scripts_["sharkMovementScript"] = []() -> scripting::components::MonoBehaviour::Instance {
    return std::make_shared<SharkMovementScript>();
  };
  scripts_["voidEaterScript"] = []() -> scripting::components::MonoBehaviour::Instance {
    return std::make_shared<VoidEaterScript>();
  };
}

scripting::components::MonoBehaviour::Instance ScriptsRegistry::GetScript(const std::string& name) {
  if (scripts_.find(name) == scripts_.end()) {
    return nullptr;
  }
  return scripts_[name]();
}
