/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** MovementSystem.cpp
*/

#include "movement_system.hpp"

using namespace zygarde::physics::systems;

MovementSystem::MovementSystem(const std::chrono::duration<float, std::milli>& deltaTime)
    : deltaTime_(deltaTime) {}

void MovementSystem::Run(
    std::shared_ptr<Registry> r,
    tools::sparse_array<std::shared_ptr<components::Rigidbody2D>>& rigidbodies,
    tools::sparse_array<std::shared_ptr<core::components::Transform>>& transforms) {
  for (size_t i = 0; i < rigidbodies.size(); ++i) {
    if (rigidbodies[i] && transforms[i]) {
      auto& rigidbody = rigidbodies[i].value();
      auto& transform = transforms[i].value();

      ComputeMovementOffset(rigidbody);
      UpdateTransformPosition(transform);
    }
  }
}

void MovementSystem::ComputeMovementOffset(
    const std::shared_ptr<components::Rigidbody2D>& rigidbody) {
  core::types::Vector2f offset;
  core::types::Vector2f velocity = rigidbody->GetVelocity();
  float deltaTimeSec = GetDeltaTimeInSeconds();

  movementOffset_.x = velocity.x * deltaTimeSec;
  movementOffset_.y = velocity.y * deltaTimeSec;
}

float MovementSystem::GetDeltaTimeInSeconds() const noexcept {
  return deltaTime_.count() / 1000.0f;
}

void MovementSystem::UpdateTransformPosition(
    const std::shared_ptr<core::components::Transform>& transform) const {
  transform->position.x += movementOffset_.x;
  transform->position.y += movementOffset_.y;
}
