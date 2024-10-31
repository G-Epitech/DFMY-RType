/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** input.hpp
*/

#pragma once
#include <SFML/Config.hpp>

#include "core/components/position/position.hpp"
#include "core/types/vector/vector_3f.hpp"
#include "registry.hpp"

namespace rtype::client::scenes::utils {

class Input {
 public:
  /**
   * @brief Create an input text
   * @param registry Registry to create the input text
   * @param tag Tag Name of the input text
   * @param text Starting text
   * @param position Position
   * @param alignment Alignment
   */
  static void Create(const Registry::Ptr& registry, const std::string& tag,
                     core::types::Vector3f position, core::components::Alignment alignment);

 private:
  /**
   * @brief Create an input field
   * @param registry Registry to create the input field
   * @param tag Tag Name of the input field
   * @param position Position
   * @param alignment Alignment
   */
  static void CreateInputField(Registry::Ptr registry, std::string tag,
                               core::types::Vector3f position,
                               core::components::Alignment alignment);

  /**
   * @brief Create a blinking cursor
   * @param registry Registry to create the blinking cursor
   * @param tag Tag Name of the blinking cursor
   * @param text Starting text
   * @param position Position
   * @param alignment Alignment
   */
  static void CreateBlinkingCursor(Registry::Ptr registry, std::string tag,
                                   core::types::Vector3f position,
                                   core::components::Alignment alignment);

  /**
   * @brief Function to handle the blinking cursor
   * @param registry Registry to handle the blinking cursor
   * @param cursor Cursor entity
   * @param unicode Unicode of the input
   * @param tag Tag Name of the blinking cursor
   */
  static void BlinkingCursorFunction(const Registry::Ptr& registry, const Entity& cursor,
                                     const sf::Uint32& unicode, const std::string& tag);
};

}  // namespace rtype::client::scenes::utils
