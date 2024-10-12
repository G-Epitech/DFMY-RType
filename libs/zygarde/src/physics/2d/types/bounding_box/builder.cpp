/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** BoundingBox2DBuilder.cpp
*/

#include "builder.hpp"

using namespace zygarde::physics::types;

BoundingBox2D BoundingBox2DBuilder::build(const zygarde::core::components::Position &position,
                                          const zygarde::core::types::Vector2f &size) noexcept {
  BoundingBox2D boundingBox;

  ResolveVerticalBounds(position, &boundingBox, size);
  ResolveHorizontalBounds(position, &boundingBox, size);
  return boundingBox;
}

void BoundingBox2DBuilder::ResolveVerticalBounds(
    const zygarde::core::components::Position &position, BoundingBox2D *bounding_box,
    zygarde::core::types::Vector2f size) noexcept {
  switch (position.aligns.horizontal) {
    case core::components::HorizontalAlign::kLeft:
      bounding_box->left = position.point.x;
      bounding_box->right = position.point.x + size.x;
      break;
    case core::components::HorizontalAlign::kCenter:
      bounding_box->left = position.point.x - size.x / 2;
      bounding_box->right = position.point.x + size.x / 2;
      break;
    default:
      bounding_box->left = position.point.x - size.x;
      bounding_box->right = position.point.x;
      break;
  }
}

void BoundingBox2DBuilder::ResolveHorizontalBounds(
    const zygarde::core::components::Position &position, BoundingBox2D *bounding_box,
    zygarde::core::types::Vector2f size) noexcept {
  switch (position.aligns.horizontal) {
    case core::components::HorizontalAlign::kLeft:
      bounding_box->left = position.point.x;
      bounding_box->right = position.point.x + size.x;
      break;
    case core::components::HorizontalAlign::kCenter:
      bounding_box->left = position.point.x - size.x / 2;
      bounding_box->right = position.point.x + size.x / 2;
      break;
    default:
      bounding_box->left = position.point.x - size.x;
      bounding_box->right = position.point.x;
      break;
  }
}
