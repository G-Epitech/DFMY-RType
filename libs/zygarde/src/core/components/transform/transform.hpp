/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** transform.hpp
*/

#pragma once

#include "core/types/vector/vector_3f.hpp"
#include "libs/zygarde/src/api.hpp"

namespace zygarde::core::components {
class EXPORT_ZYGARDE_API Transform final {
 public:
  Transform() = default;
  ~Transform() = default;

  /**
   * @brief Construct a new Transform object
   * @param position Position vector
   * @param scale Scale vector
   * @param rotation Rotation vector
   */
  Transform(types::Vector3f position, types::Vector3f scale, types::Vector3f rotation);

 public:
  /// @brief Position vector
  types::Vector3f position;
  /// @brief Scale vector
  types::Vector3f scale;
  /// @brief Rotation vector
  types::Vector3f rotation;
};
}  // namespace zygarde::core::components
