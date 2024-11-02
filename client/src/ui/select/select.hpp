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
#include "libs/zygarde/src/core/components/components.hpp"
#include "libs/zygarde/src/registry.hpp"

namespace rtype::client::ui {

using namespace zygarde::core::components;
using namespace rtype::client::components;
using namespace zygarde::core::types;
using namespace rtype::client::components;
using namespace mew::sets::drawable;

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
    /// @brief Selected option of the select
    std::optional<std::string> selectedOption = std::nullopt;
    /// @brief Color when an option is selected
    sf::Color selectedColor = sf::Color(116, 117, 116);
    /// @brief Color when no option are available
    sf::Color disabledColor = sf::Color(43, 43, 43);
    /// @brief Hover color of the select
    sf::Color hoveredColor = sf::Color(148, 148, 148);
  };

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
   * @brief Update a select
   * @param registry Registry to update the select
   * @param props Properties of the select
   */
  static void Update(const Registry::Ptr& registry, const Properties& props);

  /**
   * @brief Get the value of a select
   * @param registry Registry to get the value
   * @param id Id of the select
   * @return Current value of the select
   */
  static std::optional<std::string> GetValue(const Registry::Ptr& registry, const std::string& id);

  /**
   * @brief Set the value of a select
   * @param registry Registry to set the value
   * @param id Id of the select
   * @param value Value to set
   * @return New value of the select
   */
  static std::optional<std::string> GetDefaultOption(const Properties& props);

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

  /**
   * @brief Get the container of a select
   * @param registry Registry to get the container
   * @param props Properties of the select
   * @param container of the select
   * @return Last container selected value
   */
  static void RemoveOldContainer(const Registry::Ptr& registry, const Select::Properties& props,
                                 SelectContainer* container);
};
}  // namespace rtype::client::ui
