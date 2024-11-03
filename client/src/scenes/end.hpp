/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** leaderboard.hpp
*/

#pragma once

#include "client/src/services/server_connection_service.hpp"
#include "libs/game/includes/api.hpp"
#include "libs/mew/src/scenes/scene_base.hpp"
#include "libs/zygarde/src/core/components/components.hpp"

namespace rtype::client::scenes {

using namespace mew::scenes;

class SceneEnd final : public SceneBase {
 public:
  /**
   * @brief Construct a new Scene Leaderboard object
   */
  explicit SceneEnd(DependenciesHandler::Ptr services);

  ~SceneEnd() override = default;

  void OnCreate() override;

  void OnActivate() override;

 private:
  /// @brief Server connection service
  services::ServerConnectionService::Ptr serverConnectionService_;

  mew::managers::SettingsManager::Ptr settingsManager_;

  /**
   * @brief Create main entity
   */
  void CreateMainEntity() const;

  /**
   * @brief Create the back button
   */
  void CreateBackButton() const;

  /**
   * @brief Create the score title
   * @param origin Origin of the title
   * @param aligns Aligns of the title
   */
  void CreateScore(const zygarde::core::types::Vector3f &origin,
                   const core::components::Alignment &aligns) const;

  /**
   * @brief Create the score info
   * @param origin Origin of the info
   * @param aligns Aligns of the title
   */
  void CreateTime(const zygarde::core::types::Vector3f &origin,
                  const core::components::Alignment &aligns) const;

  /**
   * @brief Create the score win
   * @param origin Origin of the win
   * @param aligns Aligns of the title
   */
  void CreateWin(const zygarde::core::types::Vector3f &origin,
                 const core::components::Alignment &aligns) const;
};
}  // namespace rtype::client::scenes
