/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select.hpp
*/

#pragma once

#include <SFML/Graphics/Color.hpp>

#include "client/src/components/ui/select.hpp"
#include "libs/mew/src/sets/drawable/components/components.hpp"
#include "libs/mew/src/sets/events/components/components.hpp"
#include "libs/zygarde/src/core/components/components.hpp"
#include "libs/zygarde/src/registry.hpp"

namespace rtype::client::ui {

using namespace zygarde::core::components;
using namespace rtype::client::components;
using namespace zygarde::core::types;
using namespace rtype::client::components;
using namespace mew::sets::events;

class Button {
 public:
  struct Properties {
    /// @brief Id of the button
    std::string id;
    /// @brief Label of the button
    std::string label;
    /// @brief Font name of the button
    std::string fontName = "main";
    /// @brief Position of the button
    Vector3f position;
    /// @brief Display size of the button
    Vector2f size;
    /// @brief Enabled state of the button
    bool disabled = false;
    /// @brief Default color of the button
    sf::Color color = sf::Color(116, 117, 116);
    /// @brief Color when no option are available
    sf::Color disabledColor = sf::Color(43, 43, 43);
    /// @brief Hover color of the select
    sf::Color hoveredColor = sf::Color(148, 148, 148);
    /// @brief Action of the button
    OnEventHandler<kMousePressed>::signature action;
  };

  /**
   * @brief Get the tage for a select option text
   * @param id Id of the select
   * @return Tag of the select option text
   */
  static inline std::string IdTagOf(const std::string& id) { return "button:id=" + id; }

  /**
   * @brief Get the tage for a select option text
   * @param id Id of the select
   * @return Tag of the select option text
   */
  static inline std::string DisabledTagOf(const std::string& id) {
    return "button:disabled:id=" + id;
  }

  /**
   * @brief Register the dependencies of the entity
   * @param registry Registry to register the dependencies
   */
  static void RegisterDependencies(const zygarde::Registry::Ptr& registry);

  /**
   * @brief Create a new select
   * @param registry Registry to create the select
   * @param props Properties of the select
   */
  static void Create(const Registry::Ptr& registry, const Properties& props);

 private:
  /**
   * @brief Create the button rectangle
   * @param registry Registry to create the button rectangle
   * @param props Properties of the button
   */
  static void CreateButtonRectangle(const Registry::Ptr& registry, const Properties& props);
};
}  // namespace rtype::client::ui
