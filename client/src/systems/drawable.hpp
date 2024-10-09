/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** drawable_system.hpp
*/

#pragma once

#include "components/drawable.hpp"
#include "components/position.hpp"
#include "libs/zygarde/src/system_abstract.hpp"
#include "window/window_manager.hpp"

namespace rtype::client::systems {

/**
 * @brief Drawable System class
 */
class DrawableSystem final : public ASystem<components::Drawable, components::Position> {
 public:
  /**
   * @brief Default constructor of a Drawable System
   * @param window_manager The window manager to display the entities
   */
  explicit DrawableSystem(WindowManager::Ptr window_manager);

  void Run(Registry::Ptr r, sparse_array<components::Drawable>::ptr drawables,
           sparse_array<components::Position>::ptr positions) override;

 private:
  /// @brief The render window to display the entities.
  WindowManager::Ptr windowManager_;

  /// @brief This Sprite is a utils that avoid us to recreate a new sprite each time we want to
  /// display a new entity.
  sf::Sprite sprite_;
};

}  // namespace rtype::client::systems
