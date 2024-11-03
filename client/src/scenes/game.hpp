/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** game.hpp
*/

#pragma once

#include "client/src/services/server_connection_service.hpp"
#include "libs/mew/src/scenes/scene_base.hpp"
#include "libs/zygarde/src/utils/timer/timer.hpp"

namespace rtype::client::scenes {

using namespace mew::scenes;

class SceneGame final : public SceneBase {
 public:
  /**
   * @brief Construct a new Scene Game object
   * @param context Context to use
   */
  explicit SceneGame(DependenciesHandler::Ptr services);

  /**
   * @brief Default destructor
   */
  ~SceneGame() override = default;

  void Update(DeltaTime delta_time) override;

  void OnActivate() override;

 protected:
  void OnCreate() override;

 private:
  /**
   * @brief Create the scene controls
   */
  void CreateControls();

  /**
   * @brief Create the player entity
   */
  void CreatePlayerEntity();

  /**
   * @brief Key press event handler
   * @param key Key pressed
   */
  void OnKeyPress(const sf::Keyboard::Key &key);

  /**
   * @brief Load resources
   */
  void LoadResources();

  /**
   * @brief Init fade
   */
  void InitFade();

  /**
   * @brief Reset fade
   */
  void ResetFade();

  /// @brief Server connection service
  services::ServerConnectionService::Ptr serverConnectionService_;

  /// @brief Delta time
  zygarde::utils::Timer::Nanoseconds deltaTime_{};

  /// @brief Last time point
  DeltaTime lastTimePoint_{};
};
}  // namespace rtype::client::scenes
