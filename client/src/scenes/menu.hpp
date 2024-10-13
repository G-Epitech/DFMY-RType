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

  void Update(client::utils::DeltaTime delta_time) override;

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

  /**
   * @brief Check the server connection
   */
  void CreateServerConnectionLabel() const;

  /**
   * @brief Get the connection label color
   * @return sf::Color The connection label color
   */
  [[nodiscard]] sf::Color GetConnectionLabelColor() const;

  /**
   * @brief Get the connection label text
   * @return std::string The connection label text
   */
  [[nodiscard]] std::string GetConnectionLabelText() const;

  /**
   * @brief Update the connection label
   */
  void UpdateConnectionLabel() const;
};
}  // namespace rtype::client::scenes
