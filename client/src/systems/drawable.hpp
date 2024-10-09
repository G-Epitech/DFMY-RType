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
#include "managers/resources_manager.hpp"
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
   * @param resources_manager The resources manager to get the textures and fonts
   */
  explicit DrawableSystem(WindowManager::Ptr window_manager,
                          const ResourcesManager &resources_manager);

  void Run(Registry::Ptr r, sparse_array<components::Drawable>::ptr drawables,
           sparse_array<components::Position>::ptr positions) override;

 private:
  /// @brief The render window to display the entities.
  WindowManager::Ptr windowManager_;

  /// @brief This Sprite is a utils that avoid us to recreate a new sprite each time we want to
  /// display a new entity.
  sf::Sprite sprite_;

  /// @brief This Text is a utils that avoid us to recreate a new text each time we want to
  /// display a new entity.
  sf::Text text_;

  /// @brief The resources manager to get the textures and fonts.
  const ResourcesManager &resourcesManager_;

  /**
   * @brief Draw an entity
   * @param drawable The drawable component of the entity
   * @param position The position component of the entity
   */
  void DrawEntity(const components::Drawable &drawable, const components::Position &position);

  /**
   * @brief Draw a texture
   * @param texture The texture component of the entity
   * @param position The position component of the entity
   */
  void DrawEntityTexture(const components::Texture &texture, const components::Position &position);

  /**
   * @brief Draw a text
   * @param text The text component of the entity
   * @param position The position component of the entity
   */
  void DrawEntityText(const components::Text &text, const components::Position &position);
};

}  // namespace rtype::client::systems
