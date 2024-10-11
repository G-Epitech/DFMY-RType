/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** settings.hpp
*/

#pragma once

#include "bases/scene_base.hpp"
#include "context/global_context.hpp"

namespace rtype::client {
class SceneSettings final : public SceneBase<GlobalContext> {
 public:
  explicit SceneSettings(const GlobalContext &context);
  ~SceneSettings() override = default;

  void Update(utils::DeltaTime delta_time) override;

  void OnCreate() override;

  void OnActivate() override;

 private:
  /**
   * @brief Create the title
   */
  void CreateTitle() const;

  /**
   * @brief Create the back button
   */
  void CreateBackButton() const;

  /**
   * @brief Create the fullscreen button
   * @param x The x position of the button (Vertical axis).
   * @param y The y position of the button (Horizontal axis).
   */
  void CreateFullscreenButton(const float &x, const float &y) const;
};
}  // namespace rtype::client
