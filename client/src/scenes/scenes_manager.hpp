/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** scene_manager.hpp
*/

#pragma once

#include <map>
#include <string>
#include <typeindex>

#include "scene_interface.hpp"

namespace rtype::client {

template <typename ContextType>
class ScenesManager {
 public:
  /**
   * @brief Construct a new Scenes Manager object
   */
  explicit ScenesManager(const ContextType &context);

  /**
   * @brief Destroy the Scenes Manager object
   */
  ~ScenesManager() = default;

  /**
   * @brief Register a scene
   * @tparam T Scene to register
   */
  template <SceneType T>
  void RegisterScene();

  /**
   * @brief Go to a scene
   * @tparam T Scene to go to
   */
  template <SceneType T>
  void GoToScene();

  /**
   * @brief Update the current scene
   * @param delta_time Delta time
   */
  void Update(utils::DeltaTime delta_time);

  /**
   * @brief Draw the current scene
   */
  void Draw();

  /**
   * @brief Quit the application
   */
  void Quit();

  /**
   * @brief Check if the scenes manager has active scenes and has not been quit
   * @return Active state of the scenes manager
   */
  [[nodiscard]] bool IsActive() const;

  /**
   * @brief Pointer type of the scenes manager
   */
  using Ptr = std::shared_ptr<ScenesManager>;

  class Exception : public std::exception {
   public:
    /**
     * @brief Construct a new scenes manager exception
     * @param msg Message of the exception
     */
    explicit Exception(std::string msg);

    [[nodiscard]] const char *what() const noexcept override;

   private:
    // Message of the exception
    std::string msg_;
  };

 private:
  /**
   * @brief Map of scenes
   */
  using ScenesMap = std::map<std::type_index, IScene::Ptr>;

  // Map of scenes
  ScenesMap scenesMap_;

  /**
   * @brief Global context of the app
   */
  const ContextType &context_;

  /**
   * @brief Active state of the scenes manager
   */
  bool active_ = true;

  /**
   * @brief Current scene
   */
  IScene::Ptr currentScene_ = nullptr;

  /**
   * @brief Switch to a scene
   * @param new_scene New scene to switch to
   */
  void SwitchToScene(IScene::Ptr new_scene);

  /**
   * @brief Create a scene of a specific type
   * @tparam T Scene type to create
   * @return Created scene
   */
  template <SceneType T>
  IScene::Ptr CreateScene();
};
}  // namespace rtype::client

#include "scenes_manager.tpp"
