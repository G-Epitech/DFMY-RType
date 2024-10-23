/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** scene_base.hpp
*/

#pragma once

#include "./scene_interface.hpp"
#include "libs/zygarde/src/registry.hpp"
#include "managers/provider.hpp"

namespace mew::scenes {
class SceneBase : public IScene {
 protected:
  /**
   * @brief Build common scene with global context
   * @param context Context provided by the scenes manager
   */
  explicit SceneBase(const managers::DependenciesHandler &context);

  /**
   * @brief Destroy the scene
   */
  ~SceneBase() override = default;

  /// @brief Store the context provided by the scenes manager
  const ContextType &context_;

  /// @brief Store the ECS registry for the scene
  zygarde::Registry::Ptr registry_;

  /// @brief Store the resources manager
  ResourcesManager::Ptr resourcesManager_;

  /// @brief Store the sound manager
  SoundManager::Ptr soundManager_;

  /// @brief Store the game manager
  GameManager::Ptr gameManager_;

 public:
  /**
   * @brief Update the scene
   * @param delta_time Time since last update
   */
  void Update(client::utils::DeltaTime delta_time) override;

  /**
   * @brief Called when the scene is created
   */
  void OnCreate() override;

  /**
   * @brief Called when the scene is destroyed
   */
  void OnDestroy() override;

  /**
   * @brief Called when the scene is switched to
   */
  void OnActivate() override;

  /**
   * @brief Called when the scene is switched from
   */
  void OnDeactivate() override;
};
}  // namespace mew::scenes

#include "scene_base.tpp"
