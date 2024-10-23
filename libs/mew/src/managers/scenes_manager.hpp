/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** scene_manager.hpp
*/

#pragma once

#include <map>
#include <memory>
#include <string>
#include <typeindex>

#include "./manager_base.hpp"
#include "./window_manager.hpp"
#include "libs/mew/src/scenes/scene_interface.hpp"

namespace mew::managers {

class ScenesManager : public ManagerBase {
 public:
  /// @brief Pointer type of the scenes manager
  typedef std::shared_ptr<ScenesManager> Ptr;

  /**
   * @brief Construct a new Scenes Manager object
   */
  explicit ScenesManager(DependenciesHandler::Ptr services);

  /**
   * @brief Destroy the Scenes Manager object
   */
  ~ScenesManager() = default;

  /**
   * @brief Register a scene
   * @tparam T Scene to register
   */
  template <scenes::SceneType T>
  void RegisterScene();

  /**
   * @brief Go to a scene
   * @tparam T Scene to go to
   */
  template <scenes::SceneType T>
  void GoToScene();

  /**
   * @brief Update the current scene
   * @param delta_time Delta time
   */
  void Update(zygarde::utils::Timer::Nanoseconds delta_time);

  /**
   * @brief Quit the application
   */
  void Quit();

  /**
   * @brief Check if the scenes manager has active scenes and has not been quit
   * @return Active state of the scenes manager
   */
  [[nodiscard]] bool IsActive() const;

  class Exception : public std::exception {
   public:
    /**
     * @brief Construct a new scenes manager exception
     * @param msg Message of the exception
     */
    explicit Exception(std::string msg);

    [[nodiscard]] const char *what() const noexcept override;

   private:
    /// @brief Message of the exception
    std::string msg_;
  };

 private:
  /// @brief Map of scenes
  using ScenesMap = std::map<std::type_index, scenes::IScene::Ptr>;

  /// @brief Map of scenes
  ScenesMap scenesMap_;

  /// @brief Window manager
  WindowManager::Ptr windowManager_;

  /// @brief Active state of the scenes manager
  bool active_ = true;

  /// @brief Current scene
  scenes::IScene::Ptr currentScene_ = nullptr;

  /**
   * @brief Switch to a scene
   * @param new_scene New scene to switch to
   */
  void SwitchToScene(scenes::IScene::Ptr new_scene);

  /**
   * @brief Create a scene of a specific type
   * @tparam T Scene type to create
   * @return Created scene
   */
  template <scenes::SceneType T>
  scenes::IScene::Ptr CreateScene();
};
}  // namespace mew::managers

#include "./scenes_manager.tpp"
