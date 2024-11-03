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
#include "managers/settings_manager.hpp"
#include "registry.hpp"

using namespace mew::managers;

namespace rtype::client::scenes::utils {

class Input {
 public:
  /**
   * @brief Create an input text
   * @warning Please add the UtilsInputCursorSystem to the registry
   * @param registry Registry to create the input text
   * @param tag Tag Name of the input text
   * @param position Position
   * @param alignment Alignment
   * @param character_size Character size
   * @param disabled Disabled
   */
  static void Create(
      const Registry::Ptr& registry, const std::string& tag, core::types::Vector3f position,
      core::components::Alignment alignment = {core::components::HorizontalAlign::kCenter,
                                               core::components::VerticalAlign::kCenter},
      unsigned int character_size = 20, bool disabled = false);

 private:
  /**
   * @brief Create an input field
   * @param registry Registry to create the input field
   * @param tag Tag Name of the input field
   * @param position Position
   * @param alignment Alignment
   * @param character_size Character size
   * @param disabled Disabled
   */
  static void CreateInputField(const Registry::Ptr& registry, const std::string& tag,
                               const core::types::Vector3f& position,
                               core::components::Alignment alignment, unsigned int character_size, bool disabled);

  /**
   * @brief Create a blinking cursor
   * @param registry Registry to create the blinking cursor
   * @param tag Tag Name of the blinking cursor
   * @param position Position
   * @param alignment Alignment
   * @param character_size Character size
   * @param disabled Disabled
   */
  static void CreateBlinkingCursor(const Registry::Ptr& registry, const std::string& tag,
                                   const core::types::Vector3f& position,
                                   core::components::Alignment alignment,
                                   unsigned int character_size, bool disabled);
};

}  // namespace rtype::client::scenes::utils
