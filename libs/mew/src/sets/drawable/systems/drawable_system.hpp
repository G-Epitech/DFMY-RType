/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** drawable_system.hpp
*/

#pragma once

#include "libs/mew/include/api.hpp"
#include "libs/mew/src/managers/resources_manager.hpp"
#include "libs/mew/src/managers/window_manager.hpp"
#include "libs/mew/src/sets/drawable/components/components.hpp"
#include "libs/zygarde/src/core/components/components.hpp"
#include "libs/zygarde/src/system_abstract.hpp"

namespace mew::sets::drawable {

/**
 * @brief Drawable System class
 */
class EXPORT_MEW_API DrawableSystem final
    : public ASystem<Drawable, zygarde::core::components::Position> {
 public:
  /**
   * @brief Default constructor of a Drawable System
   * @param window_manager The window manager to display the entities
   * @param resources_manager The resources manager to get the textures and fonts
   */
  explicit DrawableSystem(managers::WindowManager::Ptr window_manager,
                          managers::ResourcesManager::Ptr resources_manager);

  void Run(Registry::Ptr r,
           zipper<drawable::Drawable, zygarde::core::components::Position> components) override;

 private:
  /// @brief The render window to display the entities.
  managers::WindowManager::Ptr windowManager_;

  /// @brief The resources manager to get the textures and fonts.
  managers::ResourcesManager::Ptr resourcesManager_;

  /// @brief This Sprite is a utils that avoid us to recreate a new sprite each time we want to
  /// display a new entity.
  sf::Sprite sprite_;

  /// @brief This Text is a utils that avoid us to recreate a new text each time we want to
  /// display a new entity.
  sf::Text text_;

  /// @brief This RectangleShape is a utils that avoid us to recreate a new rectangle each time we
  /// display a new entity.
  sf::RectangleShape shape_;

  /**
   * @brief Draw an entity
   * @param drawable The drawable component of the entity
   * @param position The position component of the entity
   */
  void DrawEntity(Drawable *drawable, const zygarde::core::components::Position &position);

  /**
   * @brief Draw a texture
   * @param texture The texture component of the entity
   * @param position The position component of the entity
   * @param shader The shader to apply to the texture
   */
  void DrawEntityTexture(const Texture &texture,
                         const zygarde::core::components::Position &position,
                         const std::shared_ptr<sf::Shader> &shader);

  /**
   * @brief Draw a text
   * @param text The text component of the entity
   * @param position The position component of the entity
   * @param shader The shader to apply to the text
   */
  void DrawEntityText(const Text &text, const zygarde::core::components::Position &position,
                      const std::shared_ptr<sf::Shader> &shader);

  /**
   * @brief Draw a rectangle
   * @param rectangle The rectangle component of the entity
   * @param position The position component of the entity
   * @param shader The shader to apply to the rectangle
   */
  void DrawEntityRectangle(const Rectangle &rectangle,
                           const zygarde::core::components::Position &position,
                           const std::shared_ptr<sf::Shader> &shader);

  /**
   * @brief Get the origin of the entity
   * @param position Position of the entity
   * @param bounds Bounds of the entity
   * @return Position of the origin
   */
  static std::tuple<float, float> GetOrigin(const zygarde::core::components::Position &position,
                                            const sf::FloatRect &bounds);
};

}  // namespace mew::sets::drawable
