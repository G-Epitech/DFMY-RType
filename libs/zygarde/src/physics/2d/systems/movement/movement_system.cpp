/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** MovementSystem.cpp
*/

#include "movement_system.hpp"

using namespace zygarde::physics::systems;

MovementSystem::MovementSystem(const utils::Timer::Nanoseconds& deltaTime)
    : deltaTime_(deltaTime) {}

void MovementSystem::Run(std::shared_ptr<Registry> r,
                         tools::sparse_array<components::Rigidbody2D>::ptr rigidbodies,
                         tools::sparse_array<core::components::Transform>::ptr transforms) {
  auto max = std::max(rigidbodies->size(), transforms->size());
  for (size_t i = 0; i < max; ++i) {
    auto& rigidbody = (*rigidbodies)[i];
    auto& transform = (*transforms)[i];
    if (rigidbody && transform) {
      ComputePositionOffset(&(*rigidbody));
      UpdateTransformPosition(&((*transform)));
    }
  }
}

void MovementSystem::ComputePositionOffset(components::Rigidbody2D* rigidbody) {
  core::types::Vector2f velocity = rigidbody->GetVelocity();

  if (deltaTime_.count() == 0) {
    movementOffset_ = core::types::Vector2f::zero();
    return;
  }
  float deltaTimeSec = utils::Timer::ToSeconds(deltaTime_);
  movementOffset_.x = velocity.x * deltaTimeSec;
  movementOffset_.y = velocity.y * deltaTimeSec;
}

void MovementSystem::UpdateTransformPosition(core::components::Transform* transform) const {
  transform->position.x += movementOffset_.x;
  transform->position.y += movementOffset_.y;
}
