/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** move.hpp
*/

#pragma once
#include "core/components/position/position.hpp"
#include "core/components/tags/tags.hpp"
#include "managers/window_manager.hpp"
#include "physics/2d/components/rigidbody/rigidbody_2d.hpp"
#include "system_abstract.hpp"

using namespace zygarde::physics::components;
using namespace zygarde::core::components;

class MoveSystem final : public ASystem<Tags, Rigidbody2D> {
 public:
  explicit MoveSystem(mew::managers::WindowManager::Ptr window_manager);

  void Run(Registry::Ptr r, ZippedComponents components) override;

 private:
  mew::managers::WindowManager::Ptr windowManager_;
};
