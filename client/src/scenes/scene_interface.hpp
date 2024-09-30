/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** scene_interface.hpp
*/

#pragma once

#include "context/global_context.hpp"

namespace rtype::client {
class IScene {
 public:
  virtual ~IScene() = default;

  /**
   * @brief Inject the global context into the scene
   * @param ctx Context to inject
   */
  virtual void InjectGlobalContext(GlobalContext::Ptr context) = 0;

  /**
   * @brief Run the scene
   */
  virtual void Run() = 0;
};
}  // namespace rtype::client
