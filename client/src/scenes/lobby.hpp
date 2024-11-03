/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** menu.hpp
*/

#pragma once

#include <thread>

#include "client/src/services/server_connection_service.hpp"
#include "libs/mew/src/scenes/scene_base.hpp"

namespace rtype::client::scenes {

using namespace mew::scenes;

class SceneLobby final : public SceneBase {
 public:
  /**
   * @brief Construct a new Lobby Scene object
   * @param services Services provider
   */
  explicit SceneLobby(DependenciesHandler::Ptr services);

  ~SceneLobby() override;

  void Update(DeltaTime delta_time) override;

  void OnCreate() override;

  void OnActivate() override;

 private:
  /**
   * @brief Create the title
   */
  enum class LobbyStatus {
    kNone,                    ///< No status
    kFailed,                  ///< Failed to join the lobby
    kRegistrationInProgress,  ///< Registration in progress
    kRegistered,              ///< Registered in on the server
    kJoining,                 ///< Joining the lobby
    kWaitingPlayers,          ///< Waiting for players
    kIn,                      ///< In the lobby
  };

  /**
   * @brief Create the logo
   */
  void CreateGEpitechLogo();

  /**
   * @brief Create the title
   */
  void CreateStatusText();

  /**
   * @brief Join the lobby
   */
  void JoinLobby();

  /**
   * @brief Join the lobby asynchronously
   */
  void JoinLobbyAsync();

  /**
   * @brief Update the status text
   */
  void UpdateStatusText();

  /**
   * @brief Wait for the game to start
   */
  void WaitGameStart();

  /// @brief The current lobby status
  LobbyStatus status_ = LobbyStatus::kNone;

  /// @brief Joining thread
  std::optional<std::thread> joiningThread_;

  /// @brief The main status text entity
  std::string secondaryMessage_;

  /// @brief The main status text entity
  std::string mainMessage_;

  /// @brief Reference to the server connection service
  services::ServerConnectionService::Ptr serverConnectionService_;
};
}  // namespace rtype::client::scenes
