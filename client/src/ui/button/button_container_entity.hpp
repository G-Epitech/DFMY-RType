/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select_entity.hpp
*/

#pragma once

#include <SFML/System/Vector2.hpp>

#include "./button.hpp"
#include "libs/mew/src/sets/events/events.hpp"
#include "libs/zygarde/src/core/components/components.hpp"
#include "libs/zygarde/src/registry.hpp"

namespace rtype::client::ui {
class ButtonContainerEntity final : Entity {
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
  ButtonContainerEntity(std::size_t idx, std::shared_ptr<Registry> registry);

  ~ButtonContainerEntity() final = default;

  /**
   * @brief Create the select field
   * @param props Properties of the select field
   */
  void OnSpawn(const Button::Properties& props);

 private:
  /**
   * @brief On mouse moved event
   * @param props Properties of the button
   * @param entity Current entity
   * @param props Properties of the select
   * @param pos Position of the mouse
   * @param target Target of the event
   */
  static void OnHover(const Button::Properties& props, const Entity& entity,
                      const mew::sets::events::MouseEventTarget& target);

  /**
   * @brief On mouse click event
   * @param props Properties of the button
   * @param registry Registry
   * @param entity Current entity
   * @param button Button clicked
   * @param pos Position of the mouse
   * @param target Target of the event
   */
  static void OnClick(const Button::Properties& props, const Entity& entity,
                      const sf::Mouse::Button& button, const sf::Vector2f& pos,
                      const mew::sets::events::MouseEventTarget& target);
};
}  // namespace rtype::client::ui
