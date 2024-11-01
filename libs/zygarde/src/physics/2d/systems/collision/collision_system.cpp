/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CollisionSystem.cpp
*/

#include "collision_system.hpp"

#include <algorithm>

using namespace zygarde::physics::systems;

void CollisionSystem::Run(
    std::shared_ptr<Registry> registry,
    zipper<components::Rigidbody2D, core::components::Position, components::BoxCollider2D>
        componentSet) {
  const auto start = componentSet.begin();
  const auto end = componentSet.end();

  for (auto it = start; it != end; ++it) {
    auto &&[index, entityComponents] = ~it;
    auto &&[rigidbody, position, collider] = entityComponents;

    EntityComponents selfComponents = {&rigidbody, &position, &collider,
                                       registry->EntityFromIndex(index)};

    for (auto otherIt = start; otherIt != end; ++otherIt) {
      auto &&[otherIndex, otherEntityComponents] = ~otherIt;
      auto &&[otherRigidbody, otherPosition, otherCollider] = otherEntityComponents;

      if (index == otherIndex) {
        continue;
      }

      EntityComponents otherComponents = {&otherRigidbody, &otherPosition, &otherCollider,
                                          registry->EntityFromIndex(otherIndex)};

      if (CheckCollision(selfComponents, otherComponents)) {
        ResolveCollision(selfComponents, otherComponents);
      }
    }
  }
}

bool CollisionSystem::HasMatchingCollisionLayers(
    const components::BoxCollider2D &self_collider,
    const components::BoxCollider2D &other_collider) noexcept {
  auto &selfIncludeLayers = self_collider.GetIncludeLayers();
  auto &otherCollisionLayers = other_collider.GetCollisionLayers();

  for (const auto &layer : selfIncludeLayers) {
    const auto findRes = std::find(otherCollisionLayers.begin(), otherCollisionLayers.end(), layer);
    if (findRes != otherCollisionLayers.end()) {
      return true;
    }
  }
  return false;
}

bool CollisionSystem::CheckCollision(const EntityComponents &self_pack,
                                     const EntityComponents &other_pack) noexcept {
  core::components::Position simulatedPos1 =
      GetSimulatedPosition(self_pack.rigidbody, self_pack.position);
  core::components::Position simulatedPos2 =
      GetSimulatedPosition(other_pack.rigidbody, other_pack.position);

  auto selfBoundingBox =
      types::BoundingBox2DBuilder::build(simulatedPos1, self_pack.boxCollider->GetSize());
  auto otherBoundingBox =
      types::BoundingBox2DBuilder::build(simulatedPos2, other_pack.boxCollider->GetSize());

  return CheckBoundingBoxOverlap(selfBoundingBox, otherBoundingBox);
}

bool CollisionSystem::CheckBoundingBoxOverlap(
    const physics::types::BoundingBox2D &self_bounding_box,
    const physics::types::BoundingBox2D &other_bounding_box) noexcept {
  bool overlapX = self_bounding_box.left <= other_bounding_box.right &&
                  self_bounding_box.right >= other_bounding_box.left;

  bool overlapY = self_bounding_box.top <= other_bounding_box.bottom &&
                  self_bounding_box.bottom >= other_bounding_box.top;

  return overlapX && overlapY;
}

core::components::Position CollisionSystem::GetSimulatedPosition(
    physics::components::Rigidbody2D *rigidbody, core::components::Position *position) noexcept {
  core::components::Position simulatedPosition;

  simulatedPosition.aligns = position->aligns;
  simulatedPosition.point.x = position->point.x + rigidbody->GetMovementOffset().x;
  simulatedPosition.point.y = position->point.y + rigidbody->GetMovementOffset().y;
  simulatedPosition.point.z = position->point.z;
  return simulatedPosition;
}

void CollisionSystem::ResolveCollision(const EntityComponents &self_pack,
                                       const EntityComponents &other_pack) noexcept {
  if (HasMatchingCollisionLayers(*self_pack.boxCollider, *other_pack.boxCollider)) {
    if (!self_pack.rigidbody->IsKinematic() && !other_pack.rigidbody->IsKinematic()) {
      self_pack.rigidbody->SetMovementOffset(core::types::Vector2f::zero());
    }
    self_pack.boxCollider->AddCollision(BuildCollision2D(self_pack, other_pack));
  }
}

physics::types::Collision2D CollisionSystem::BuildCollision2D(
    const EntityComponents &self_pack, const EntityComponents &other_pack) noexcept {
  return {self_pack.rigidbody, self_pack.position, other_pack.rigidbody, other_pack.position,
          other_pack.entity};
}
