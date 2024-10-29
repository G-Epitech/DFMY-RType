/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** entity.hpp
*/

#pragma once

#include <cstddef>
#include <memory>
#include <type_traits>

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
  virtual ~Entity();

  /**
   * @brief Copy constructor
   * @param other Entity to copy
   */
  Entity(const Entity& other);

  /**
   * @brief Operator size_t
   */
  explicit operator std::size_t() const;

  /**
   * @brief Operator =
   * @param other Entity to copy
   * @return Copied entity
   */
  Entity& operator=(const Entity& other);

  /**
   * @brief Operator ==
   * @param other Entity to compare
   * @return Match result
   */
  bool operator==(const Entity& other) const;

  /**
   * @brief Get the component
   * @tparam Component Component to get
   * @return Component*
   */
  template <typename Component>
  Component* GetComponent();

 protected:
  friend class Registry;

  /// @brief Entity id
  std::size_t id_;
  /// @brief Registry reference
  std::shared_ptr<Registry> registry_;

  /**
   * @brief Private constructor
   * Even if this constructor is private, the registry class can access it
   * @param idx Entity id
   * @param registry Registry reference
   */
  explicit Entity(std::size_t idx, std::shared_ptr<Registry> registry);

  /**
   * @brief OnSpawn method
   * This method is called when the entity is spawned.
   * This method is virtual and can be overridden
   */
  virtual void OnSpawn();
};

/// @brief Entity type concept
template <class T>
concept EntityType = std::is_base_of_v<Entity, T>;

}  // namespace zygarde
