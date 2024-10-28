/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** position_system.cpp
*/

#include "position_system.hpp"

using namespace zygarde::physics::systems;

void PositionSystem::Run(std::shared_ptr<Registry> r,
                         tools::sparse_array<components::Rigidbody2D>::ptr rigidbodies,
                         tools::sparse_array<core::components::Position>::ptr positions) {
  auto max = std::max(rigidbodies->size(), positions->size());
  for (size_t i = 0; i < max; i++) {
    if (!r->HasEntityAtIndex(i)) {
      continue;
    }
    auto& rigidbody = (*rigidbodies)[i];
    auto& position = (*positions)[i];
    if (rigidbody.has_value() && position.has_value()) {
      ApplyMovementOffset(&(*rigidbody), &(*position));
    }
  }
}

void PositionSystem::ApplyMovementOffset(physics::components::Rigidbody2D* rigidbody,
                                         core::components::Position* position) {
  core::types::Vector2f movementOffset = rigidbody->GetMovementOffset();
  position->point.x += movementOffset.x;
  position->point.y += movementOffset.y;
}
