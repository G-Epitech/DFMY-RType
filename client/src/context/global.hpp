/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** global_context.hpp
*/

#pragma once

#include <memory>

#include "managers/game_manager.hpp"
#include "managers/scenes_manager.hpp"
#include "managers/server_connection_manager.hpp"
#include "managers/sound_manager.hpp"

namespace rtype::client {

struct GlobalContext {
  using Ptr = std::shared_ptr<GlobalContext>;

  /**
   * @brief Provide access to the window manager
   */
  WindowManager::Ptr windowManager;

  /**
   * @brief Provide access to the scenes manager
   */
  ScenesManager<GlobalContext>::Ptr scenesManager;

  /**
   * @brief Provide access to the sound manager
   */
  SoundManager::Ptr soundManager;

  /**
   * @brief Provide access to the game manager
   */
  GameManager::Ptr gameManager;

  /**
   * @brief Provide access to the client API
   */
  ServerConnectionManager::Ptr serverConnectionManager;
};
}  // namespace rtype::client
