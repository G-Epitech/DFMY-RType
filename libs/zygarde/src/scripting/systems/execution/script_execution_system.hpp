/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ScriptExecutionSystem.hpp
*/

#pragma once

#include "api.hpp"
#include "physics/2d/components/box_collider/box_collider_2d.hpp"
#include "scripting/components/script/script.hpp"
#include "system_abstract.hpp"

namespace zygarde::scripting::systems {
class EXPORT_ZYGARDE_API ScriptExecutionSystem final
    : public ASystem<scripting::components::Script, physics::components::BoxCollider2D> {

 public:
  ScriptExecutionSystem() = default;
  ~ScriptExecutionSystem() override = default;

  void Run(Registry::Ptr r, sparse_array<physics::components::BoxCollider2D>::ptr box_collider,
           sparse_array<scripting::components::Script>::ptr script) override;
};
}  // namespace zygarde::scripting::systems
