/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select.hpp
*/

#pragma once

#include "libs/zygarde/src/core/components/components.hpp"
#include "libs/zygarde/src/registry.hpp"

namespace rtype::client::ui {
class Select {
 public:
  struct Properties {
    /// @brief Id of the select
    std::string id;
    /// @brief Position of the select
    zygarde::core::types::Vector3f position;
    /// @brief Display size of the select
    zygarde::core::types::Vector2f size;
    /// @brief Options of the select
    std::map<std::string, std::string> options;
  };

  /**
   * @brief Register the dependencies of the entity
   * @param registry Registry to register the dependencies
   */
  static void RegisterDependencies(zygarde::Registry& registry);

  /**
   * @brief Get the id tag of the select
   * @param id Id of the select
   * @return Tag of the select
   */
  static inline std::string IdTagOf(const std::string& id) { return "select:id=" + id; }

  /**
   * @brief Get the value tag of the select
   * @param id Id of the select
   * @return Tag of the select
   */
  static inline std::string ValueTagOf(const std::string& id) { return "select:value:id=" + id; }

  /**
   * @brief Create a new select
   * @param registry Registry to create the select
   * @param props Properties of the select
   */
  static void Create(const Registry::Ptr& registry, const Properties& props);

 private:
  /**
   * @brief Create the select field
   * @param registry Registry to create the select field
   * @param props Properties of the select field
   */
  static void CreateSelectField(const Registry::Ptr& registry, const Properties& props);
};
}  // namespace rtype::client::ui
