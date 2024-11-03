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
    kNone,     ///< No status
    kWaiting,  ///< Waiting for the lobby
    kIn,       ///< In the lobby
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
  void Wait();

  /**
   * @brief Join the lobby asynchronously
   */
  void WaitAsync();

  /**
   * @brief Update the status text
   */
  void UpdateStatusText();

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
