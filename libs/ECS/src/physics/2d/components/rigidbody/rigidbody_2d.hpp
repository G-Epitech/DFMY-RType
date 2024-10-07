/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Rigidbody2D.hpp
*/

#pragma once

#include "libs/ECS/src/core/types/vector/vector_2f.hpp"

namespace rtype::sdk::ECS::physics::components {
class Rigidbody2D final {
 public:
  Rigidbody2D() = default;
  ~Rigidbody2D() = default;

  Rigidbody2D(const Rigidbody2D &other) = default;
  Rigidbody2D &operator=(const Rigidbody2D &other) = default;
  Rigidbody2D(Rigidbody2D &&other) noexcept = default;
  Rigidbody2D &operator=(Rigidbody2D &&other) noexcept = default;

 public:
  void AddForce(core::types::vector_2f force) noexcept;
  [[maybe_unused]] void AddForce(float x, float y) noexcept;

 private:
  core::types::vector_2f velocity_;
};
}  // namespace rtype::sdk::ECS::physics::components
