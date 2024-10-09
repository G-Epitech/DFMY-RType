/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CollisionSystem.cpp
*/

#include "collision_system.hpp"

using namespace zygarde::physics::systems;

CollisionSystem::CollisionSystem(const utils::Timer::Nanoseconds &deltaTime)
    : deltaTime_(deltaTime) {}

void CollisionSystem::Run(std::shared_ptr<Registry> r,
                          sparse_array<components::Rigidbody2D *> &rigidbodies,
                          sparse_array<core::components::Transform *> &transforms,
                          sparse_array<components::BoxCollider2D *> &colliders) {
  return;
}
