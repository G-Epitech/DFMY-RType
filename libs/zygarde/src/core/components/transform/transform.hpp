/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** transform.hpp
*/

#pragma once

#include <memory>

#include "libs/zygarde/src/api.hpp"
#include "libs/zygarde/src/core/types/vector/vector_3f.hpp"

namespace zygarde::core::components {
class EXPORT_ZYGARDE_API Transform final {
 public:
  using ptr = std::shared_ptr<Transform>;
  using const_ptr = std::shared_ptr<Transform const>;

 public:
  Transform() = default;
  ~Transform() = default;

  /**
   * @brief Construct a new Transform object
   * @param scale Scale vector
   * @param rotation Rotation vector
   */
  Transform(types::Vector3f scale, types::Vector3f rotation);

 public:
  /// @brief Scale vector
  types::Vector3f scale;
  /// @brief Rotation vector
  types::Vector3f rotation;
};
}  // namespace zygarde::core::components
