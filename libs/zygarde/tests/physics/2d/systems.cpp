/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** systems.cpp
*/

#include <gtest/gtest.h>

#include "physics/2d/systems/movement/movement_system.hpp"
#include "registry.hpp"
#include "system_abstract.hpp"
#include "tools/zipper.hpp"

TEST(Physics2DSystemsTests, NoMovement) {
  utils::Timer::Nanoseconds delta_time{std::chrono::nanoseconds{1000000000}};
  const auto registry = Registry::create();
  registry->RegisterComponent<physics::components::Rigidbody2D>();
  registry->RegisterComponent<core::components::Position>();
  registry->AddSystem<physics::systems::MovementSystem>(delta_time);
  const auto entity = registry->SpawnEntity();
  registry->AddComponent<physics::components::Rigidbody2D>(entity,
                                                           physics::components::Rigidbody2D());
  registry->AddComponent<core::components::Position>(entity, core::components::Position());
  registry->RunSystems();
  const auto position = registry->GetComponent<core::components::Position>(entity);
  ASSERT_EQ(position->point, core::types::Vector3f::zero());
}

TEST(Physics2DSystemsTests, BasicMovement) {
  utils::Timer::Nanoseconds delta_time{std::chrono::nanoseconds{1000000000}};
  const auto registry = Registry::create();
  registry->RegisterComponent<physics::components::Rigidbody2D>();
  registry->RegisterComponent<core::components::Position>();
  registry->AddSystem<physics::systems::MovementSystem>(delta_time);
  const auto entity = registry->SpawnEntity();
  core::types::Vector2f velocity{1, 1};
  registry->AddComponent<physics::components::Rigidbody2D>(
      entity, physics::components::Rigidbody2D(velocity));
  registry->AddComponent<core::components::Position>(entity, core::components::Position());
  registry->RunSystems();
  const auto position = registry->GetComponent<core::components::Position>(entity);
  ASSERT_EQ(position->point, core::types::Vector3f(1, 1, 0));
}
