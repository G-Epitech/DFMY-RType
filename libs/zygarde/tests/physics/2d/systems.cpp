/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** systems.cpp
*/

#include <gtest/gtest.h>

#include "physics/2d/systems/collision/collision_system.hpp"
#include "physics/2d/systems/movement/movement_system.hpp"
#include "physics/2d/systems/position/position_system.hpp"
#include "registry.hpp"
#include "system_abstract.hpp"
#include "tools/zipper.hpp"

TEST(Physics2DSystemsTests, NoMovement) {
  utils::Timer::Nanoseconds delta_time{std::chrono::nanoseconds{1000000000}};
  const auto registry = Registry::Create();
  registry->RegisterComponent<physics::components::Rigidbody2D>();
  registry->RegisterComponent<core::components::Position>();
  registry->AddSystem<physics::systems::MovementSystem>(delta_time);
  const auto entity = registry->SpawnEntity();
  registry->AddComponent<physics::components::Rigidbody2D>(entity,
                                                           physics::components::Rigidbody2D());
  registry->AddComponent<core::components::Position>(entity, core::components::Position());
  registry->RunSystems();
  const auto position = registry->GetComponent<core::components::Position>(entity);
  ASSERT_EQ((*position)->point, core::types::Vector3f::zero());
}

TEST(Physics2DSystemsTests, BasicMovement) {
  utils::Timer::Nanoseconds delta_time{std::chrono::nanoseconds{1000000000}};
  const auto registry = Registry::Create();
  registry->RegisterComponent<physics::components::Rigidbody2D>();
  registry->RegisterComponent<core::components::Position>();
  registry->AddSystem<physics::systems::MovementSystem>(delta_time);
  registry->AddSystem<physics::systems::PositionSystem>();
  const auto entity = registry->SpawnEntity();
  core::types::Vector2f velocity{1, 1};
  registry->AddComponent<physics::components::Rigidbody2D>(
      entity, physics::components::Rigidbody2D(velocity, false, 0.0));
  registry->AddComponent<core::components::Position>(entity, core::components::Position());
  registry->RunSystems();
  const auto position = registry->GetComponent<core::components::Position>(entity);
  ASSERT_EQ((*position)->point, core::types::Vector3f(1, 1, 0));
}

TEST(Physics2DSystemsTests, MultipleMovement) {
  utils::Timer::Nanoseconds delta_time{std::chrono::nanoseconds{1000000000}};
  const auto registry = Registry::Create();
  registry->RegisterComponent<physics::components::Rigidbody2D>();
  registry->RegisterComponent<core::components::Position>();
  registry->AddSystem<physics::systems::MovementSystem>(delta_time);
  registry->AddSystem<physics::systems::PositionSystem>();
  const auto entity1 = registry->SpawnEntity();
  core::types::Vector2f velocity1{1, 1};
  registry->AddComponent<physics::components::Rigidbody2D>(
      entity1, physics::components::Rigidbody2D(velocity1, false, 0.0));
  registry->AddComponent<core::components::Position>(entity1, core::components::Position());
  const auto entity2 = registry->SpawnEntity();
  core::types::Vector2f velocity2{2, 2};
  registry->AddComponent<physics::components::Rigidbody2D>(
      entity2, physics::components::Rigidbody2D(velocity2, false, 0.0));
  registry->AddComponent<core::components::Position>(entity2, core::components::Position());
  registry->RunSystems();
  const auto position1 = registry->GetComponent<core::components::Position>(entity1);
  const auto position2 = registry->GetComponent<core::components::Position>(entity2);
  ASSERT_EQ((*position1)->point, core::types::Vector3f(1, 1, 0));
  ASSERT_EQ((*position2)->point, core::types::Vector3f(2, 2, 0));
}

TEST(Physics2DSystemsTests, NoCollision) {
  const auto registry = Registry::Create();
  registry->RegisterComponent<physics::components::Rigidbody2D>();
  registry->RegisterComponent<core::components::Position>();
  registry->RegisterComponent<physics::components::BoxCollider2D>();
  registry->AddSystem<physics::systems::CollisionSystem>();
  const auto entity1 = registry->SpawnEntity();
  registry->AddComponent<physics::components::Rigidbody2D>(entity1,
                                                           physics::components::Rigidbody2D());
  registry->AddComponent<core::components::Position>(entity1, core::components::Position());
  registry->AddComponent<physics::components::BoxCollider2D>(
      entity1, physics::components::BoxCollider2D(core::types::Vector2f(1, 1)));
  const auto entity2 = registry->SpawnEntity();
  registry->AddComponent<physics::components::Rigidbody2D>(entity2,
                                                           physics::components::Rigidbody2D());
  registry->AddComponent<core::components::Position>(
      entity2, core::components::Position(core::types::Vector3f(2, 2, 0)));
  registry->AddComponent<physics::components::BoxCollider2D>(
      entity2, physics::components::BoxCollider2D(core::types::Vector2f(1, 1)));
  registry->RunSystems();
  const auto boxCollider1 = registry->GetComponent<physics::components::BoxCollider2D>(entity1);
  const auto boxCollider2 = registry->GetComponent<physics::components::BoxCollider2D>(entity2);
  ASSERT_FALSE((*boxCollider1)->HasCollision());
  ASSERT_FALSE((*boxCollider2)->HasCollision());
}

TEST(Physics2DSystemsTests, BasicCollision) {
  const auto registry = Registry::Create();
  registry->RegisterComponent<physics::components::Rigidbody2D>();
  registry->RegisterComponent<core::components::Position>();
  registry->RegisterComponent<physics::components::BoxCollider2D>();
  registry->AddSystem<physics::systems::CollisionSystem>();
  const auto entity1 = registry->SpawnEntity();
  registry->AddComponent<physics::components::Rigidbody2D>(entity1,
                                                           physics::components::Rigidbody2D());
  registry->AddComponent<core::components::Position>(entity1, core::components::Position());
  registry->AddComponent<physics::components::BoxCollider2D>(
      entity1, physics::components::BoxCollider2D(core::types::Vector2f(1, 1)));
  const auto entity2 = registry->SpawnEntity();
  registry->AddComponent<physics::components::Rigidbody2D>(entity2,
                                                           physics::components::Rigidbody2D());
  registry->AddComponent<core::components::Position>(entity2, core::components::Position());
  registry->AddComponent<physics::components::BoxCollider2D>(
      entity2, physics::components::BoxCollider2D(core::types::Vector2f(1, 1)));
  registry->RunSystems();
  const auto boxCollider1 = registry->GetComponent<physics::components::BoxCollider2D>(entity1);
  const auto boxCollider2 = registry->GetComponent<physics::components::BoxCollider2D>(entity2);
  ASSERT_TRUE((*boxCollider1)->HasCollision());
  ASSERT_TRUE((*boxCollider2)->HasCollision());
}
