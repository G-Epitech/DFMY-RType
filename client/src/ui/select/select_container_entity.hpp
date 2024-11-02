/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select_entity.hpp
*/

#pragma once

#include <SFML/System/Vector2.hpp>

#include "./select.hpp"
#include "libs/mew/src/sets/events/events.hpp"
#include "libs/zygarde/src/core/components/components.hpp"
#include "libs/zygarde/src/registry.hpp"

namespace rtype::client::ui {
class SelectContainerEntity final : Entity {
  friend class zygarde::Registry;

 public:
  /**
   * @brief Register the dependencies of the entity
   * @param registry Registry to register the dependencies
   */
  static void RegisterDependencies(const zygarde::Registry::Ptr& registry);

 protected:
  /**
   * @brief Construct a new Select Entity object
   * @param props Properties of the select
   */
  SelectContainerEntity(std::size_t idx, std::shared_ptr<Registry> registry);

  ~SelectContainerEntity() final = default;

  /**
   * @brief Create the select field
   * @param props Properties of the select field
   */
  void OnSpawn(const Select::Properties& props);

 private:
  /**
   * @brief On mouse moved event
   * @param entity Current entity
   * @param props Properties of the select
   * @param pos Position of the mouse
   * @param target Target of the event
   */
  static void OnHover(const Entity& entity, const mew::sets::events::MouseEventTarget& target);

  /**
   * @brief On mouse click event
   * @param registry Registry
   * @param entity Current entity
   * @param button Button clicked
   * @param target Target of the event
   */
  static void OnClick(const Entity& entity, const sf::Mouse::Button& button,
                      const mew::sets::events::MouseEventTarget& target);
};
}  // namespace rtype::client::ui
