/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** global_context.hpp
*/

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

#include "managers/scenes_manager.hpp"

namespace rtype::client {

struct GlobalContext {
  using Ptr = std::shared_ptr<GlobalContext>;

  /**
   * @brief Provide access to the app window
   */
  std::shared_ptr<sf::RenderWindow> window;

  /**
   * @brief Provide access to the scenes manager
   */
  ScenesManager<GlobalContext>::Ptr scenesManager;
};
}  // namespace rtype::client
