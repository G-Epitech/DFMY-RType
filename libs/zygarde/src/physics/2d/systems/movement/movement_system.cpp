/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** MovementSystem.cpp
*/

#include "movement_system.hpp"

using namespace zygarde::physics::systems;

MovementSystem::MovementSystem(const utils::Timer::Nanoseconds& delta_time)
    : ASystem(), deltaTime_(delta_time) {}

void MovementSystem::Run(std::shared_ptr<Registry> r,
                         tools::sparse_array<components::Rigidbody2D>::ptr rigidbodies,
                         tools::sparse_array<core::components::Position>::ptr positions) {
  auto max = std::max(rigidbodies->size(), positions->size());
  for (size_t i = 0; i < max; ++i) {
    auto& rigidbody = (*rigidbodies)[i];
    auto& position = (*positions)[i];
    if (rigidbody && position) {
      ComputePositionOffset(&(*rigidbody));
      UpdatePosition(&((*position)));
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

void MovementSystem::UpdatePosition(core::components::Position* position) const {
  position->point.x += movementOffset_.x;
  position->point.y += movementOffset_.y;
}
