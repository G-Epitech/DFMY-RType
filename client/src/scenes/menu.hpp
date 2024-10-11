/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** menu.hpp
*/

#pragma once

#include "bases/scene_base.hpp"
#include "context/global.hpp"

namespace rtype::client::scenes {
class SceneMenu final : public SceneBase<GlobalContext> {
 public:
  explicit SceneMenu(const GlobalContext &context);
  ~SceneMenu() override = default;

  void Update(utils::DeltaTime delta_time) override;

  void OnCreate() override;

  void OnActivate() override;

 private:
  /**
   * @brief Create the title
   */
  void CreateTitle() const;

  /**
   * @brief Create the play button
   */
  void CreatePlayButton() const;

  /**
   * @brief Create the settings button
   */
  void CreateSettingsButton() const;

  /**
   * @brief Create the exit button
   */
  void CreateExitButton() const;
};
}  // namespace rtype::client::scenes
