/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** entity.hpp
*/

#pragma once

#include <cstddef>

#include "libs/zygarde/src/api.hpp"

namespace zygarde {

/**
 * @brief Entity class
 * This class is used to represent an entity in the ECS system
 */
class EXPORT_ZYGARDE_API Entity {
 public:
  /**
   * @brief Default constructor
   */
  ~Entity();

  /**
   * @brief Operator size_t
   */
  explicit operator std::size_t() const;

  Entity operator=(const Entity& other) const;

 private:
  /// @brief Entity id
  const std::size_t id_;

  /**
   * @brief Private constructor
   * Even if this constructor is private, the registry class can access it
   * @param idx Entity id
   */
  explicit Entity(std::size_t idx);

  friend class Registry;
};
}  // namespace zygarde
