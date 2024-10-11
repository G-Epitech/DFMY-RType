/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** RegistryHelper.cpp
*/

#include "registry_helper.hpp"

#include <utility>

using namespace zygarde::utils;

void RegistryHelper::RegisterBaseComponents(Registry *registry) {
  RegisterCoreComponents(registry);
  RegisterPhysicsComponents(registry);
}

void RegistryHelper::RegisterCoreComponents(Registry *registry) {
  registry->RegisterComponent<core::components::Transform>();
}

void RegistryHelper::RegisterPhysicsComponents(Registry *registry) {
  registry->RegisterComponent<physics::components::BoxCollider2D>();
  registry->RegisterComponent<physics::components::Rigidbody2D>();
}

void RegistryHelper::RegisterBaseSystems(Registry *registry, const Timer::Nanoseconds &deltaTime) {
  RegisterPhysicsSystems(registry, deltaTime);
}

void RegistryHelper::RegisterPhysicsSystems(Registry *registry,
                                            const Timer::Nanoseconds &deltaTime) {
  registry->AddSystem<physics::systems::MovementSystem>(deltaTime);
}
