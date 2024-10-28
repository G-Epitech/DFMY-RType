/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CollisionSystem.cpp
*/

#include "collision_system.hpp"

#include <iostream>

#include "physics/2d/types/bounding_box/builder.hpp"

using namespace zygarde::physics::systems;

void CollisionSystem::Run(std::shared_ptr<Registry> r,
                          sparse_array<components::Rigidbody2D>::ptr rigidbodies,
                          sparse_array<core::components::Position>::ptr positions,
                          sparse_array<components::BoxCollider2D>::ptr colliders) {
  for (size_t i = 0; i < positions->size(); i++) {
    if (!r->HasEntityAtIndex(i)) {
      continue;
    }
    if (!IndexHasRequiredComponents(i, rigidbodies, positions, colliders)) {
      continue;
    }
    auto componentsPack = GetComponentsPackAtIndex(r, i, rigidbodies, positions, colliders);

    for (size_t j = 0; j < positions->size(); j++) {
      if (i == j) {
        continue;
      }
      if (!r->HasEntityAtIndex(j)) {
        continue;
      }
      if (!IndexHasRequiredComponents(j, rigidbodies, positions, colliders)) {
        continue;
      }
      auto otherComponentsPack = GetComponentsPackAtIndex(r, j, rigidbodies, positions, colliders);

      if (AreColliding(componentsPack, otherComponentsPack)) {
        ProcessCollision(componentsPack, otherComponentsPack);
      }
    }
  }
}

bool CollisionSystem::IndexHasRequiredComponents(
    size_t index, const sparse_array<components::Rigidbody2D>::ptr &rigidbodies,
    const sparse_array<core::components::Position>::ptr &positions,
    const sparse_array<components::BoxCollider2D>::ptr &colliders) noexcept {
  if (index >= rigidbodies->size() || index >= positions->size() || index >= colliders->size()) {
    return false;
  }
  return ((*rigidbodies)[index].has_value() && (*positions)[index].has_value() &&
          (*colliders)[index].has_value());
}

CollisionSystem::ComponentsPack CollisionSystem::GetComponentsPackAtIndex(
    Registry::Const_Ptr r, size_t index,
    const sparse_array<components::Rigidbody2D>::ptr &rigidbodies,
    const sparse_array<core::components::Position>::ptr &positions,
    const sparse_array<components::BoxCollider2D>::ptr &colliders) {
  return {&(*rigidbodies)[index].value(), &(*positions)[index].value(),
          &(*colliders)[index].value(), r->EntityFromIndex(index)};
}

bool CollisionSystem::HaveCommonCollisionLayers(
    const components::BoxCollider2D &collider1,
    const components::BoxCollider2D &collider2) noexcept {
  auto &includeLayers1 = collider1.GetIncludeLayers();
  auto &collisionLayers2 = collider2.GetCollisionLayers();

  for (const auto &layer : includeLayers1) {
    const auto findRes = std::find(collisionLayers2.begin(), collisionLayers2.end(), layer);
    if (findRes != collisionLayers2.end()) {
      return true;
    }
  }
  return false;
}

bool CollisionSystem::AreColliding(const ComponentsPack &pack1,
                                   const ComponentsPack &pack2) noexcept {
  core::components::Position simulatedPosition1;
  simulatedPosition1.aligns = pack1.position->aligns;
  simulatedPosition1.point.x = pack1.position->point.x + pack1.rigidbody->GetMovementOffset().x;
  simulatedPosition1.point.y = pack1.position->point.y + pack1.rigidbody->GetMovementOffset().y;
  simulatedPosition1.point.z = pack1.position->point.z;

  core::components::Position simulatedPosition2;
  simulatedPosition2.aligns = pack2.position->aligns;
  simulatedPosition2.point.x = pack2.position->point.x + pack2.rigidbody->GetMovementOffset().x;
  simulatedPosition2.point.y = pack2.position->point.y + pack2.rigidbody->GetMovementOffset().y;
  simulatedPosition2.point.z = pack2.position->point.z;

  auto boundingBox1 =
      types::BoundingBox2DBuilder::build(simulatedPosition1, pack1.boxCollider->GetSize());
  auto boundingBox2 =
      types::BoundingBox2DBuilder::build(simulatedPosition2, pack2.boxCollider->GetSize());

  bool overlapX =
      boundingBox1.left <= boundingBox2.right && boundingBox1.right >= boundingBox2.left;
  bool overlapY =
      boundingBox1.top <= boundingBox2.bottom && boundingBox1.bottom >= boundingBox2.top;
  return overlapX && overlapY;
}

void CollisionSystem::ProcessCollision(const ComponentsPack &pack1,
                                       const ComponentsPack &pack2) noexcept {
  if (HaveCommonCollisionLayers(*pack1.boxCollider, *pack2.boxCollider)) {
    if (!pack1.rigidbody->IsKinematic() && !pack2.rigidbody->IsKinematic()) {
      pack1.rigidbody->SetMovementOffset(core::types::Vector2f::zero());
    }
    pack1.boxCollider->AddCollision(BuildCollision2D(pack1, pack2));
  }
}
physics::types::Collision2D CollisionSystem::BuildCollision2D(
    const ComponentsPack &pack1, const ComponentsPack &pack2) noexcept {
  return {pack1.rigidbody, pack1.position, pack2.rigidbody, pack2.position, pack2.entity};
}
