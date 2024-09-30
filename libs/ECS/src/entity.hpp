/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** entity.hpp
*/

#pragma once

#include <cstddef>

#include "api.hpp"

namespace rtype::sdk::ECS {

/**
 * @brief Entity class
 * This class is used to represent an entity in the ECS system
 */
EXPORT_ECS_SDK_API class Entity {
 public:
  /**
   * @brief Default constructor
   */
  ~Entity();

  /**
   * @brief Operator size_t
   */
  explicit operator std::size_t() const;

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
}  // namespace rtype::sdk::ECS
