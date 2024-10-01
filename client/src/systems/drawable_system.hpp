/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** drawable_system.hpp
*/

#pragma once

#include <libs/ECS/src/system_abstract.hpp>

#include "components/drawable_component.hpp"
#include "components/position_component.hpp"

using namespace rtype::sdk::ECS;

namespace rtype::client::systems {

/**
 * @brief Drawable System class
 */
class DrawableSystem final : public ASystem<components::Drawable, components::Position> {
 public:
  /**
   * @brief Default constructor of a Drawable System
   */
  explicit DrawableSystem(const std::shared_ptr<sf::RenderWindow>& window);

  void Run(Registry* r, sparse_array<components::Drawable>& drawables,
           sparse_array<components::Position>& positions) override;

 private:
  /// @brief The render window to display the entities.
  std::shared_ptr<sf::RenderWindow> window_;

  /// @brief This Sprite is a utils that avoid us to recreate a new rectangle each time we want to
  /// display a new entity.
  sf::Sprite sprite_;
};

}  // namespace rtype::client::systems
