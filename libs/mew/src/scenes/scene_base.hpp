/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** scene_base.hpp
*/

#pragma once

#include "./scene_interface.hpp"
#include "libs/mew/src/managers/managers.hpp"
#include "libs/porygon/src/handler.hpp"
#include "libs/zygarde/src/registry.hpp"

namespace mew::scenes {
class SceneBase : public IScene {
 public:
  /**
   * @brief Update the scene
   * @param delta_time Time since last update
   */
  void Update(DeltaTime delta_time) override;

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

 protected:
  /**
   * @brief Build common scene with global context
   * @param context Context provided by the scenes manager
   */
  explicit SceneBase(porygon::DependenciesHandler::Ptr services);

  /**
   * @brief Destroy the scene
   */
  ~SceneBase() override = default;

  /// @brief Store the context provided by the scenes manager
  porygon::DependenciesHandler::Ptr services_;

  /// @brief Store the ECS registry for the scene
  zygarde::Registry::Ptr registry_;

  /// @brief Store the resources manager
  managers::DefaultManagers defaultManagers_;

 private:
  /**
   * @brief Initialize the registry
   */
  void InitializeRegistry();

  /**
   * @brief Register the default systems
   */
  void AddDefaultSystems();

  /**
   * @brief Register the default components
   */
  void RegisterDefaultComponents();
};
}  // namespace mew::scenes
