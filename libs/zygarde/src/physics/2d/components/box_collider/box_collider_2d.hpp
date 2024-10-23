/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** box_collider_2_d.hpp
*/

#pragma once

#include "libs/zygarde/src/api.hpp"
#include "libs/zygarde/src/core/types/vector/vector_2f.hpp"
#include "libs/zygarde/src/physics/2d/components/collider/collider_2d.hpp"

namespace zygarde::physics::components {
class EXPORT_ZYGARDE_API BoxCollider2D final {
 public:
  using ptr = std::shared_ptr<BoxCollider2D>;

 public:
  BoxCollider2D() = delete;

  /**
   * @brief Construct a new BoxCollider2D object
   * @param size Size of the box
   */
  explicit BoxCollider2D(const core::types::Vector2f &size);

  /**
   * @brief Construct a new BoxCollider2D object
   * @param size Size of the box
   * @param collision_layers Collision layers
   */
  BoxCollider2D(const core::types::Vector2f &size, std::vector<int> collision_layers,
                std::vector<int> include_layers);

 public:
  /**
   * @brief Get the size of the box
   */
  [[nodiscard]] const core::types::Vector2f &GetSize() const noexcept { return size_; }

  /**
   * @brief Set the size of the box
   */
  void SetSize(const core::types::Vector2f &size);

  [[nodiscard]] const std::vector<int> &GetCollisionLayers() const noexcept {
    return collider_.collisionLayers_;
  }

  /**
   * @brief Get the include layers of the underlying collider
   * @return collision layer array
   */
  [[nodiscard]] const std::vector<int> &GetIncludeLayers() const noexcept {
    return collider_.includeLayers_;
  }

  void AddCollision(types::Collision2D collision) noexcept;

  [[nodiscard]] bool HasCollision() const noexcept { return collider_.HasCollision(); }

  [[nodiscard]] types::Collision2D::ptr GetNextCollision() noexcept {
    return collider_.GetNextCollision();
  }

 private:
  /// @brief Size of the box
  core::types::Vector2f size_;
  /// @brief Collider2D object
  Collider2D collider_;
};
}  // namespace zygarde::physics::components
