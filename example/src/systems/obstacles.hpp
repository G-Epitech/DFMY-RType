/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** obstacles.hpp
*/

/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** move.hpp
*/

#pragma once

#include "core/components/position/position.hpp"
#include "core/components/tags/tags.hpp"
#include "managers/scenes_manager.hpp"
#include "managers/window_manager.hpp"
#include "physics/2d/components/box_collider/box_collider_2d.hpp"
#include "physics/2d/components/rigidbody/rigidbody_2d.hpp"
#include "system_abstract.hpp"
#include "utils/timer/timer.hpp"

using namespace zygarde::physics::components;
using namespace zygarde::core::components;

class ObstablesSystem final : public ASystem<Tags, Rigidbody2D, BoxCollider2D> {
 public:
  explicit ObstablesSystem(mew::managers::ScenesManager::Ptr scenesManager,
                           const zygarde::utils::Timer::Nanoseconds &delta_time);

  void Run(Registry::Ptr r, ZippedComponents components) override;

 private:
  static void CreateObstacle(Registry::Ptr r);

  const zygarde::utils::Timer::Nanoseconds &delta_time;

  sf::Clock clock_;

  mew::managers::ScenesManager::Ptr scenesManager_;
};
