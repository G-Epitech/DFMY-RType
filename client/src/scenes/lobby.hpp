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
  ~SceneLobby() override;

  void Update(client::utils::DeltaTime delta_time) override;

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

  /// @brief The current lobby status
  LobbyStatus status_ = LobbyStatus::kNone;

  /// @brief Joining thread
  std::optional<std::thread> joiningThread_;

  /// @brief The main status text entity
  std::string secondaryMessage_;

  /// @brief The main status text entity
  std::string mainMessage_;
};
}  // namespace rtype::client::scenes
