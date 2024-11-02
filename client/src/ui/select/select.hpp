/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select.hpp
*/

#pragma once

#include <SFML/Graphics/Color.hpp>

#include "libs/zygarde/src/core/components/components.hpp"
#include "libs/zygarde/src/registry.hpp"

namespace rtype::client::ui {
class Select {
 public:
  struct Properties {
    /// @brief Id of the select
    std::string id;
    /// @brief Expanded state of the select
    bool expanded = false;
    /// @brief Position of the select
    zygarde::core::types::Vector3f position;
    /// @brief Display size of the select
    zygarde::core::types::Vector2f size;
    /// @brief Placeholder of the select when no options are available
    std::string placeholder;
    /// @brief Options of the select (value/id, label)
    std::map<std::string, std::string> options;
    /// @brief Color when an option is selected
    sf::Color selectedColor = sf::Color(116, 117, 116);
    /// @brief Color when no option are available
    sf::Color disabledColor = sf::Color(43, 43, 43);
    /// @brief Hover color of the select
    sf::Color hoveredColor = sf::Color(148, 148, 148);
  };

  /**
   * @brief Get the tage for a select option text
   * @param id Id of the option
   * @return Tag of the select option text
   */
  static inline std::string OptionTextIdTagOf(const std::string& id) {
    return "select:option-text:id=" + id;
  }

  /**
   * @brief Get the tage for a select option text
   * @param id Id of the select
   * @return Tag of the select option text
   */
  static inline std::string OptionIdTagOf(const std::string& id) {
    return "select:option:id=" + id;
  }

  /**
   * @brief Get the tage for a select option text
   * @param id Id of the select
   * @return Tag of the select option text
   */
  static inline std::string ContainerTextIdTagOf(const std::string& id) {
    return "select:container-text:id=" + id;
  }

  /**
   * @brief Get the tage for a select option text
   * @param id Id of the select
   * @return Tag of the select option text
   */
  static inline std::string IdTagOf(const std::string& id) { return "select:id=" + id; }

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

  /**
   * @brief Get the value of a select
   * @param registry Registry to get the value
   * @param id Id of the select
   * @return Current value of the select
   */
  static std::optional<std::string> GetValue(const Registry::Ptr& registry, const std::string& id);

 private:
  /**
   * @brief Create the select field
   * @param registry Registry to create the select field
   * @param props Properties of the select field
   */
  static void CreateSelectField(const Registry::Ptr& registry, const Properties& props);

  /**
   * @brief Create the options of the select
   * @param registry Registry to create the options
   * @param props Properties of the options
   */
  static void CreateOptions(const Registry::Ptr& registry, const Properties& props);
};
}  // namespace rtype::client::ui
