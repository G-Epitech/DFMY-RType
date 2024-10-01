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

class ScenesManager {
 private:
  using ScenesMap = std::map<std::type_index, IScene::Ptr>;

  // Map of scenes
  ScenesMap scenesMap_;

  /**
   * @brief Global context of the app
   */
  const GlobalContext &context_;

 public:
  /**
   * @brief Construct a new Scenes Manager object
   */
  explicit ScenesManager(const GlobalContext &context);

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

 public:
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
};
}  // namespace rtype::client

#include "scenes_manager.tpp"
