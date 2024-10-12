/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CollisionSystem.cpp
*/

#include "collision_system.hpp"

#include <algorithm>

using namespace zygarde::physics::systems;

CollisionSystem::CollisionSystem(const utils::Timer::Nanoseconds &deltaTime)
    : deltaTime_(deltaTime) {}

void CollisionSystem::Run(std::shared_ptr<Registry> r,
                          tools::sparse_array<components::Rigidbody2D>::ptr rigidbodies,
                          tools::sparse_array<core::components::Transform>::ptr transforms,
                          tools::sparse_array<components::BoxCollider2D>::ptr colliders) {
  for (size_t i = 0; i < transforms->size(); i++) {
    if (!IndexHasRequiredComponents(i, rigidbodies, transforms, colliders)) {
      continue;
    }
    auto componentsPack = GetComponentsPackAtIndex(i, rigidbodies, transforms, colliders);
    for (size_t j = i + 1; j < transforms->size(); j++) {
      if (!IndexHasRequiredComponents(j, rigidbodies, transforms, colliders)) {
        continue;
      }
      auto otherComponentsPack = GetComponentsPackAtIndex(j, rigidbodies, transforms, colliders);
      if (!HaveCommonCollisionLayers(*componentsPack.boxCollider,
                                     *otherComponentsPack.boxCollider)) {
        continue;
      }
      if (AreColliding(*componentsPack.boxCollider, *otherComponentsPack.boxCollider)) {
        ProcessCollision(componentsPack, otherComponentsPack);
      }
    }
  }
}

bool CollisionSystem::IndexHasRequiredComponents(
    size_t index, const tools::sparse_array<components::Rigidbody2D>::ptr &rigidbodies,
    const tools::sparse_array<core::components::Transform>::ptr &transforms,
    const tools::sparse_array<components::BoxCollider2D>::ptr &colliders) noexcept {
  return (*rigidbodies)[index].has_value() && (*transforms)[index].has_value() &&
         (*colliders)[index].has_value();
}

CollisionSystem::ComponentsPack CollisionSystem::GetComponentsPackAtIndex(
    size_t index, const tools::sparse_array<components::Rigidbody2D>::ptr &rigidbodies,
    const tools::sparse_array<core::components::Transform>::ptr &transforms,
    const tools::sparse_array<components::BoxCollider2D>::ptr &colliders) noexcept {
  return {&(*rigidbodies)[index].value(), &(*transforms)[index].value(),
          &(*colliders)[index].value()};
}

bool CollisionSystem::HaveCommonCollisionLayers(
    physics::components::BoxCollider2D &collider1,
    physics::components::BoxCollider2D &collider2) noexcept {
  auto &collisionLayers1 = collider1.GetCollisionLayers();
  auto &collisionLayers2 = collider2.GetCollisionLayers();

  return std::find_first_of(collisionLayers1.begin(), collisionLayers1.end(),
                            collisionLayers2.begin(),
                            collisionLayers2.end()) != collisionLayers1.end();
}

bool CollisionSystem::AreColliding(physics::components::BoxCollider2D &collider1,
                                   core::components::Transform &transform1,
                                   physics::components::BoxCollider2D &collider2,
                                   core::components::Transform &transform2) noexcept {
  auto boundingBox1 = GetBoundingBox(collider1, transform1);
  auto boundingBox2 = GetBoundingBox(collider2, transform2);

  bool overlapX = boundingBox1.left < boundingBox2.right && boundingBox1.right > boundingBox2.left;
  bool overlapY = boundingBox1.top < boundingBox2.bottom && boundingBox1.bottom > boundingBox2.top;
  return overlapX && overlapY;
}

void CollisionSystem::ProcessCollision(CollisionSystem::ComponentsPack &pack1,
                                       CollisionSystem::ComponentsPack &pack2) noexcept {
  if (!pack1.rigidbody->IsKinematic()) {
    pack1.rigidbody->CancelVelocity();
  }
  if (!pack2.rigidbody->IsKinematic()) {
    pack2.rigidbody->CancelVelocity();
  }
  auto collision = BuildCollision2D(pack1, pack2);
  pack1.boxCollider->AddColllision(collision);
  pack2.boxCollider->AddColllision(collision);
}

physics::types::Collision2D CollisionSystem::BuildCollision2D(
    CollisionSystem::ComponentsPack &pack1, CollisionSystem::ComponentsPack &pack2) noexcept {
  return {pack1.rigidbody, pack1.transform, pack2.rigidbody, pack2.transform};
}
physics::types::BoundingBox2D CollisionSystem::GetBoundingBox(
    physics::components::BoxCollider2D &collider, core::components::Transform &transform) noexcept {
  core::types::Vector2f position2D(transform.position);
  return {position2D, collider.GetSize()};
}
