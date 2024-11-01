/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** position_system.cpp
*/

#include "position_system.hpp"

using namespace zygarde::physics::systems;

void PositionSystem::Run(std::shared_ptr<Registry> r,
                         zipper<components::Rigidbody2D, core::components::Position> components) {
  for (auto&& [rigidbody, position] : components) {
    ApplyMovementOffset(&rigidbody, &position);
  }
}

void PositionSystem::ApplyMovementOffset(physics::components::Rigidbody2D* rigidbody,
                                         core::components::Position* position) {
  core::types::Vector2f movementOffset = rigidbody->GetMovementOffset();
  position->point.x += movementOffset.x;
  position->point.y += movementOffset.y;
}
