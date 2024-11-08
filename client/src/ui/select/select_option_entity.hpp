/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select_option_entity.hpp
*/

#pragma once

#include <SFML/System/Vector2.hpp>

#include "./select.hpp"
#include "libs/mew/src/sets/events/events.hpp"
#include "libs/zygarde/src/core/components/components.hpp"
#include "libs/zygarde/src/registry.hpp"

namespace rtype::client::ui {
class SelectOptionEntity final : Entity {
  friend class zygarde::Registry;

 public:
  /**
   * @brief Register the dependencies of the entity
   * @param registry Registry to register the dependencies
   */
  static void RegisterDependencies(const zygarde::Registry::Ptr &registry);

 protected:
  /**
   * @brief Construct a new Select Entity object
   * @param idx Index of the entity
   * @param registry Registry to register the dependencies
   */
  SelectOptionEntity(std::size_t idx, std::shared_ptr<Registry> registry);

  ~SelectOptionEntity() final = default;

  /**
   * @brief On spawn event
   * @param index Index of the option
   * @param props Properties of the select
   * @param value Id of the option
   * @param label Text of the option
   */
  void OnSpawn(std::size_t index, const Select::Properties &props, const std::string &value,
               const std::string &label);

  /**
   * @brief On mouse click event
   * @param registry Registry
   * @param entity Entity
   */
  static void OnClick(const Registry::Ptr &registry, const Entity &entity);

  /**
   * @brief On mouse moved event
   * @param entity Entity
   * @param props Properties of the select
   * @param target Target of the event
   */
  static void OnHover(const Entity &entity, const mew::sets::events::MouseEventTarget &target);
};
}  // namespace rtype::client::ui
