/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** MovementSystem.cpp
*/

#include "./movement_system.hpp"

using namespace zygarde::physics::systems;

MovementSystem::MovementSystem(const utils::Timer::Nanoseconds& delta_time)
    : ASystem(), deltaTime_(delta_time) {}

void MovementSystem::Run(std::shared_ptr<Registry> r,
                         zipper<components::Rigidbody2D, core::components::Position> components) {
  for (auto&& [rigidbody, position] : components) {
    ApplyDrag(&(rigidbody));
    ComputePositionOffset(&(rigidbody));
  }
}

void MovementSystem::ComputePositionOffset(components::Rigidbody2D* rigidbody) {
  core::types::Vector2f velocity = rigidbody->GetVelocity();

  if (deltaTime_.count() == 0) {
    movementOffset_ = core::types::Vector2f::zero();
    return;
  }
  if (deltaTime_ > utils::Timer::Nanoseconds::zero()) {
    auto deltaTimeSec = utils::Timer::ToSeconds(deltaTime_);
    rigidbody->SetMovementOffset(
        core::types::Vector2f(velocity.x * deltaTimeSec, velocity.y * deltaTimeSec));
  } else {
    rigidbody->SetMovementOffset(core::types::Vector2f::zero());
  }
}

#include <iostream>
void MovementSystem::ApplyDrag(physics::components::Rigidbody2D* rigidbody) const {
  float drag = rigidbody->GetDrag();

  if (drag == 0) {
    return;
  }
  if (drag >= 100) {
    rigidbody->SetVelocity(core::types::Vector2f(0, 0));
    return;
  }
  if (deltaTime_ < utils::Timer::Nanoseconds::zero()) {
    return;
  }
  core::types::Vector2f velocity = rigidbody->GetVelocity();
  float deltaTimeSec = utils::Timer::ToSeconds(deltaTime_);
  std::cout << "Velocity: " << velocity.x << " " << velocity.y
            << "Magnitude: " << velocity.magnitude() << "DeltaTimeSec: " << deltaTimeSec
            << std::endl;
  if (velocity.magnitude() > 0) {
    core::types::Vector2f dragForce = -drag * velocity;
    core::types::Vector2f dragVector = dragForce * deltaTimeSec;

    if (velocity.x != 0) {
      velocity.x += dragVector.x;
    }
    if (velocity.y != 0) {
      velocity.y += dragVector.y;
    }
    if (velocity.magnitude() < 0.01f) {
      velocity = core::types::Vector2f(0, 0);
    }
  }
  rigidbody->SetVelocity(velocity);
}
