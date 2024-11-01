/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** character_base_script.hpp
*/

#pragma once

#include "types/difficulty.hpp"
#include "zygarde/src/scripting/components/mono_behaviour/mono_behaviour.hpp"

namespace rtype::server::game::scripts {
class PlayerBaseScript : public zygarde::scripting::components::MonoBehaviour {
 public:
  void SetDifficultyData(DifficultyPlayerMultipliers multipliers);

 protected:
  float health_;
  float fireRate_;
  float damage_;
  float speed_;
};
}  // namespace rtype::server::game::scripts
