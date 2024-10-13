/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CollisionSystem.cpp
*/

#include "collision_system.hpp"

#include <algorithm>
#include <iostream>

using namespace zygarde::physics::systems;

void CollisionSystem::Run(std::shared_ptr<Registry> r,
                          tools::sparse_array<components::Rigidbody2D>::ptr rigidbodies,
                          tools::sparse_array<core::components::Position>::ptr positions,
                          tools::sparse_array<components::BoxCollider2D>::ptr colliders) {
  for (size_t i = 0; i < positions->size(); i++) {
    if (!IndexHasRequiredComponents(i, rigidbodies, positions, colliders)) {
      continue;
    }
    auto componentsPack = GetComponentsPackAtIndex(r, i, rigidbodies, positions, colliders);

    for (size_t j = i + 1; j < positions->size(); j++) {
      if (!IndexHasRequiredComponents(j, rigidbodies, positions, colliders)) {
        continue;
      }
      if (!r->HasEntityAtIndex(j)) {
        break;
      }
      auto otherComponentsPack = GetComponentsPackAtIndex(r, j, rigidbodies, positions, colliders);

      if (!HaveCommonCollisionLayers(*componentsPack.boxCollider,
                                     *otherComponentsPack.boxCollider)) {
        continue;
      }
      if (AreColliding(*componentsPack.boxCollider, *componentsPack.position,
                       *otherComponentsPack.boxCollider, *otherComponentsPack.position)) {
        ProcessCollision(componentsPack, otherComponentsPack);
      }
    }
  }
}

bool CollisionSystem::IndexHasRequiredComponents(
    size_t index, const tools::sparse_array<components::Rigidbody2D>::ptr &rigidbodies,
    const tools::sparse_array<core::components::Position>::ptr &positions,
    const tools::sparse_array<components::BoxCollider2D>::ptr &colliders) noexcept {
  if (index >= rigidbodies->size() || index >= positions->size() || index >= colliders->size()) {
    return false;
  }
  return ((*rigidbodies)[index].has_value() && (*positions)[index].has_value() &&
          (*colliders)[index].has_value());
}

CollisionSystem::ComponentsPack CollisionSystem::GetComponentsPackAtIndex(
    Registry::Const_Ptr r, size_t index,
    const tools::sparse_array<components::Rigidbody2D>::ptr &rigidbodies,
    const tools::sparse_array<core::components::Position>::ptr &positions,
    const tools::sparse_array<components::BoxCollider2D>::ptr &colliders) {
  return {&(*rigidbodies)[index].value(), &(*positions)[index].value(),
          &(*colliders)[index].value(), r->EntityFromIndex(index)};
}

bool CollisionSystem::HaveCommonCollisionLayers(
    const physics::components::BoxCollider2D &collider1,
    const physics::components::BoxCollider2D &collider2) noexcept {
  auto &collisionLayers1 = collider1.GetCollisionLayers();
  auto &collisionLayers2 = collider2.GetCollisionLayers();

  return std::find_first_of(collisionLayers1.begin(), collisionLayers1.end(),
                            collisionLayers2.begin(),
                            collisionLayers2.end()) != collisionLayers1.end();
}

bool CollisionSystem::AreColliding(const physics::components::BoxCollider2D &collider1,
                                   const core::components::Position &position1,
                                   const physics::components::BoxCollider2D &collider2,
                                   const core::components::Position &position2) noexcept {
  auto boundingBox1 = types::BoundingBox2DBuilder::build(position1, collider1.GetSize());
  auto boundingBox2 = types::BoundingBox2DBuilder::build(position2, collider2.GetSize());

  bool overlapX =
      boundingBox1.left <= boundingBox2.right && boundingBox1.right >= boundingBox2.left;
  bool overlapY =
      boundingBox1.top <= boundingBox2.bottom && boundingBox1.bottom >= boundingBox2.top;
  return overlapX && overlapY;
}

void CollisionSystem::ProcessCollision(const CollisionSystem::ComponentsPack &pack1,
                                       const CollisionSystem::ComponentsPack &pack2) noexcept {
  if (!pack1.rigidbody->IsKinematic()) {
    pack1.rigidbody->CancelVelocity();
  }
  if (!pack2.rigidbody->IsKinematic()) {
    pack2.rigidbody->CancelVelocity();
  }

  pack1.boxCollider->AddColllision(BuildCollision2D(pack1, pack2));
  pack2.boxCollider->AddColllision(BuildCollision2D(pack2, pack1));
}

physics::types::Collision2D CollisionSystem::BuildCollision2D(
    const CollisionSystem::ComponentsPack &pack1,
    const CollisionSystem::ComponentsPack &pack2) noexcept {
  return {pack1.rigidbody, pack1.position, pack2.rigidbody, pack2.position, pack2.entity};
}
