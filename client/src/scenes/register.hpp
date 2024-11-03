/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** menu.hpp
*/

#pragma once

#include "client/src/services/server_connection_service.hpp"
#include "libs/mew/src/scenes/scene_base.hpp"

namespace rtype::client::scenes {

using namespace mew::scenes;

class SceneRegister final : public SceneBase {
 public:
  /**
   * @brief Construct a new Scene Menu object
   * @param services Services provider
   */
  explicit SceneRegister(DependenciesHandler::Ptr services);

  /**
   * @brief Default destructor
   */
  ~SceneRegister() final = default;

  void Update(DeltaTime delta_time) override;

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
  void CreateConnectButton() const;

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

  /// @brief Store reference to the server connection service
  services::ServerConnectionService::Ptr serverConnectionService_;
};
}  // namespace rtype::client::scenes
