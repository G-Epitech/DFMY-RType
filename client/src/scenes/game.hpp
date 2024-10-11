/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** game.hpp
*/

#pragma once

#include "bases/scene_base.hpp"
#include "context/global.hpp"

namespace rtype::client::scenes {
class SceneGame final : public SceneBase<GlobalContext> {
 public:
  /**
   * @brief Construct a new Scene Game object
   * @param context Context to use
   */
  explicit SceneGame(const GlobalContext &context);
  ~SceneGame() override = default;

 protected:
  void OnCreate() override;

 private:
  /**
   * @brief Create the scene controls
   */
  void CreateControls();

  /**
   * @brief Create the player entity
   */
  void CreatePlayerEntity();

  /**
   * @brief Key press event handler
   * @param key Key pressed
   */
  void OnKeyPress(const sf::Keyboard::Key &key);

  /**
   * @brief Load resources
   */
  void LoadResources();
};
}  // namespace rtype::client::scenes
