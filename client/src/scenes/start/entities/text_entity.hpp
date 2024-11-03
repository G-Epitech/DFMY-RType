/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** title_entity.hpp
*/

#pragma once

#include <SFML/Graphics/Color.hpp>

#include "libs/mew/src/sets/drawable/drawable.hpp"
#include "libs/zygarde/src/core/types/vector/vector.hpp"
#include "libs/zygarde/src/entity.hpp"
#include "libs/zygarde/src/registry.hpp"

namespace rtype::client::scenes {

class TextEntity : public Entity {
  friend class zygarde::Registry;

 public:
  struct Properties {
    /// @brief Text to display
    std::string text;
    /// @brief Position of the text
    zygarde::core::types::Vector3f position;
    /// @brief Font name
    std::string fontName = "main";
    /// @brief Character size
    unsigned int characterSize = 40;
    /// @brief Color of the text
    sf::Color color;
    /// @brief Layer of the text
    zygarde::core::components::Alignment alignment;
    /// @brief Style of the text*
    sf::Text::Style style = sf::Text::Style::Regular;
    /// @brief Tags list
    std::vector<std::string> tags;
    /// @brief View of the text
    bool visible = true;
  };

  /**
   * @brief Register the dependencies
   * @param registry Registry to register the dependencies
   */
  static void RegisterDependencies(const zygarde::Registry::Ptr &registry);

  explicit TextEntity(const Entity &other);

 protected:
  explicit TextEntity(std::size_t idx, std::shared_ptr<Registry> registry);

  void OnSpawn(const Properties &props);
};
}  // namespace rtype::client::scenes
