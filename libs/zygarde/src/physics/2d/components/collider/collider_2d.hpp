/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** collider.hpp
*/

#pragma once

#include <queue>
#include <vector>

#include "libs/zygarde/src/api.hpp"
#include "libs/zygarde/src/physics/2d/types/collision_2d.hpp"

namespace zygarde::physics::components {

class EXPORT_ZYGARDE_API Collider2D final {
 public:
  using ptr = std::shared_ptr<Collider2D>;

 public:
  Collider2D() = default;

 private:
  /**
   * @brief Construct a new Collider2D object
   * @param collision_layers Collision layers
   *  @param include_layers Include layers
   */
  Collider2D(std::vector<int> collision_layers, std::vector<int> include_layers);

  /**
   * @brief Check if there is a collision in the queue
   */
  [[nodiscard]] bool HasCollision() const noexcept { return !collisionQueue_.empty(); }

  /**
   * @brief Get the next collision
   */
  [[nodiscard]] types::Collision2D::ptr GetNextCollision() noexcept;

  friend class BoxCollider2D;

 private:
  /// @brief Collision layers
  std::vector<int> collisionLayers_ = std::vector{0};
  /// @brief Include collision layers
  std::vector<int> includeLayers_ = std::vector{0};
  /// @brief Incoming collisions
  std::queue<types::Collision2D::ptr> collisionQueue_;
};
}  // namespace zygarde::physics::components
