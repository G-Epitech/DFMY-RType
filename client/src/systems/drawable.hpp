/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** drawable_system.hpp
*/

#pragma once

#include <libs/zygarde/src/system_abstract.hpp>

#include "components/drawable.hpp"
#include "components/position.hpp"

using namespace zygarde::ECS;

namespace rtype::client::systems {

/**
 * @brief Drawable System class
 */
class DrawableSystem final : public ASystem<components::Drawable, components::Position> {
 public:
  /**
   * @brief Default constructor of a Drawable System
   */
  explicit DrawableSystem(std::shared_ptr<sf::RenderWindow> window);

  void Run(std::shared_ptr<Registry> r, sparse_array<components::Drawable>& drawables,
           sparse_array<components::Position>& positions) override;

 private:
  /// @brief The render window to display the entities.
  std::shared_ptr<sf::RenderWindow> window_;

  /// @brief This Sprite is a utils that avoid us to recreate a new sprite each time we want to
  /// display a new entity.
  sf::Sprite sprite_;
};

}  // namespace rtype::client::systems
