/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** scene_abstract.hpp
*/

#pragma once

#include "scene_interface.hpp"

namespace rtype::client {
template <typename ContextType>
class SceneBase : public IScene {
 protected:
  /**
   * @brief Build common scene with global context
   * @param context Context provided by the scenes manager
   */
  explicit SceneBase(const ContextType &context);

  /**
   * @brief Destroy the scene
   */
  ~SceneBase() override = default;

  /**
   * @brief Store the context provided by the scenes manager
   */
  const ContextType &context_;

 public:
  /***
   * @brief Draw the scene
   */
  void Draw() override;

  /**
   * @brief Update the scene
   * @param delta_time Time since last update
   */
  void Update(utils::DeltaTime delta_time) override;

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
}  // namespace rtype::client

#include "scene_base.tpp"
