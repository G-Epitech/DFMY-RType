/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CollisionSystem.cpp
*/

#include "collision_system.hpp"

#include <algorithm>

#include "physics/2d/types/bounding_box/builder.hpp"

using namespace zygarde::physics::systems;

void CollisionSystem::Run(std::shared_ptr<Registry> r,
                          zipper<sparse_array<components::Rigidbody2D>::ptr,
                                 sparse_array<core::components::Position>::ptr,
                                 sparse_array<components::BoxCollider2D>::ptr>
                              components) {
  const auto start = components.begin();
  const auto end = components.end();
  for (auto it = start; it != end; ++it) {
    auto &&[index, values] = ~it;
    auto &&[rigidbodies, positions, colliders] = values;
    ComponentsPack componentsPack = {&rigidbodies, &positions, &colliders,
                                     r->EntityFromIndex(index)};

    const auto startOther = it + 1;
    const auto endOther = components.end();
    for (auto itOther = startOther; itOther != endOther; ++itOther) {
      auto &&[indexOther, valuesOther] = ~itOther;
      auto &&[rigidbodiesOther, positionsOther, collidersOther] = valuesOther;
      if (index == indexOther) {
        continue;
      }
      ComponentsPack otherComponentsPack = {&rigidbodiesOther, &positionsOther, &collidersOther,
                                            r->EntityFromIndex(indexOther)};
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

bool CollisionSystem::AreColliding(const components::BoxCollider2D &collider1,
                                   const core::components::Position &position1,
                                   const components::BoxCollider2D &collider2,
                                   const core::components::Position &position2) noexcept {
  auto boundingBox1 = types::BoundingBox2DBuilder::build(position1, collider1.GetSize());
  auto boundingBox2 = types::BoundingBox2DBuilder::build(position2, collider2.GetSize());

  bool overlapX =
      boundingBox1.left <= boundingBox2.right && boundingBox1.right >= boundingBox2.left;
  bool overlapY =
      boundingBox1.top <= boundingBox2.bottom && boundingBox1.bottom >= boundingBox2.top;
  return overlapX && overlapY;
}

void CollisionSystem::ProcessCollision(const ComponentsPack &pack1,
                                       const ComponentsPack &pack2) noexcept {
  if (HaveCommonCollisionLayers(*pack1.boxCollider, *pack2.boxCollider)) {
    if (!pack1.rigidbody->IsKinematic()) {
      pack1.rigidbody->CancelVelocity();
    }
    pack1.boxCollider->AddCollision(BuildCollision2D(pack1, pack2));
  }

  if (HaveCommonCollisionLayers(*pack2.boxCollider, *pack1.boxCollider)) {
    if (!pack2.rigidbody->IsKinematic()) {
      pack2.rigidbody->CancelVelocity();
    }
    pack2.boxCollider->AddCollision(BuildCollision2D(pack2, pack1));
  }
}

physics::types::Collision2D CollisionSystem::BuildCollision2D(
    const ComponentsPack &pack1, const ComponentsPack &pack2) noexcept {
  return {pack1.rigidbody, pack1.position, pack2.rigidbody, pack2.position, pack2.entity};
}
