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
class SceneLobby final : public SceneBase<GlobalContext> {
 public:
  explicit SceneLobby(const GlobalContext &context);
  ~SceneLobby() override = default;

  void Update(client::utils::DeltaTime delta_time) override;

  void OnCreate() override;

  void OnActivate() override;

 private:
  /**
   * @brief Create the logo
   */
  void CreateGEpitechLogo();

  /**
   * @brief Create the title
   */
  void CreateStatusText();
};
}  // namespace rtype::client::scenes
