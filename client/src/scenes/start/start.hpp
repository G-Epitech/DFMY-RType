/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** start.hpp
*/

#pragma once

#include "client/src/services/server_connection_service.hpp"
#include "libs/mew/src/scenes/scene_base.hpp"

namespace rtype::client::scenes {

using namespace mew::scenes;

class SceneStart final : public SceneBase {
 public:
  /**
   * @brief Construct a new Start Scene object
   * @param services Services to be injected
   */
  explicit SceneStart(DependenciesHandler::Ptr services);

  /**
   * @brief Destroy the Start Scene object
   */
  ~SceneStart() final = default;

 private:
  void OnCreate() override;

  /**
   * @brief Add the static labels
   */
  void CreateStaticLabels();

  /// @brief Server connection service
  services::ServerConnectionService::Ptr serverConnectionService_;
};
}  // namespace rtype::client::scenes
