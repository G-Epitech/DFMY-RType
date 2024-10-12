/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** RegistryHelper.cpp
*/

#include "registry_helper.hpp"

#include <utility>

using namespace zygarde::utils;

void RegistryHelper::RegisterBaseComponents(const std::shared_ptr<Registry> &registry) {
  RegisterCoreComponents(registry);
  RegisterPhysicsComponents(registry);
}

void RegistryHelper::RegisterCoreComponents(const std::shared_ptr<Registry> &registry) {
  registry->RegisterComponent<core::components::Transform>();
}

void RegistryHelper::RegisterPhysicsComponents(const std::shared_ptr<Registry> &registry) {
  registry->RegisterComponent<physics::components::BoxCollider2D>();
  registry->RegisterComponent<physics::components::Rigidbody2D>();
}

void RegistryHelper::RegisterBaseSystems(const std::shared_ptr<Registry> &registry,
                                         const Timer::Nanoseconds &delta_time) {
  RegisterPhysicsSystems(registry, delta_time);
}

void RegistryHelper::RegisterPhysicsSystems(const std::shared_ptr<Registry> &registry,
                                            const Timer::Nanoseconds &delta_time) {
  registry->AddSystem<physics::systems::MovementSystem>(delta_time);
  registry->AddSystem<physics::systems::CollisionSystem>();
}
