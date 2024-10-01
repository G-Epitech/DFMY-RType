/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** global_context.hpp
*/

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

namespace rtype::client {
class ScenesManager;

struct GlobalContext {
  using Ptr = std::shared_ptr<GlobalContext>;

  /**
   * @brief Provide access to the app window
   */
  std::shared_ptr<sf::RenderWindow> window;

  /**
   * @brief Provide access to the scenes manager
   */
  std::shared_ptr<ScenesManager> scenesManager;
};
}  // namespace rtype::client
