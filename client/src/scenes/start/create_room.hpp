/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** create_room.hpp
*/

#pragma once

#include "client/src/services/server_connection_service.hpp"
#include "libs/mew/src/scenes/scene_base.hpp"

#define CREATE_ROOM_PIXEL_LEFT 600

namespace rtype::client::scenes {

using namespace mew::scenes;

class SceneCreateRoom final : public SceneBase {
 public:
  /**
   * @brief Construct a new Scene Menu object
   * @param services Services provider
   */
  explicit SceneCreateRoom(DependenciesHandler::Ptr services);

  /**
   * @brief Default destructor
   */
  ~SceneCreateRoom() final = default;

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
  void CreateCreateButton() const;

  /**
   * @brief Create the exit button
   */
  void CreateBackButton() const;

  void CreateInputLabel();

  void CreateDifficulty();

  void CreateDifficultyLabel();

  void CreateDifficultyNumbers();

  void CreateDifficultyNumber(unsigned int number, const sf::Vector2f& pos);

  void CreateNbPlayers();

  void CreateNbPlayersLabel();

  void CreateNbPlayersNumbers();

  void CreateNbPlayersNumber(unsigned int number, const sf::Vector2f& pos);

  /// @brief Store reference to the server connection service
  services::ServerConnectionService::Ptr serverConnectionService_;

  /// @brief Store reference to the settings manager
  mew::managers::SettingsManager::Ptr settingsManager_;

  /// @brief Store reference to the scenes manager
  mew::managers::ScenesManager::Ptr scenesManager_;

  /// @brief Store the number of players
  unsigned int nbPlayers_{0};

  /// @brief Store the difficulty
  unsigned int difficulty_{0};
};
}  // namespace rtype::client::scenes
