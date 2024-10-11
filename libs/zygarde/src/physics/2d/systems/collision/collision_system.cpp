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
                                   physics::components::BoxCollider2D &collider2) noexcept {
  auto boundingBox1 = collider1.GetBoundingBox();
  auto boundingBox2 = collider2.GetBoundingBox();

  bool overlapX = boundingBox1.left < boundingBox2.right && boundingBox1.right > boundingBox2.left;
  bool overlapY = boundingBox1.top < boundingBox2.bottom && boundingBox1.bottom > boundingBox2.top;
  return overlapX && overlapY;
}
