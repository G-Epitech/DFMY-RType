/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select_value_entity.hpp
*/

#pragma once

#include "./select.hpp"
#include "libs/zygarde/src/core/components/components.hpp"
#include "libs/zygarde/src/registry.hpp"

namespace rtype::client::ui {
class SelectContainerTextEntity final : Entity {
  friend class zygarde::Registry;

 public:
  /**
   * @brief Register the dependencies of the entity
   * @param registry Registry to register the dependencies
   */
  static void RegisterDependencies(const zygarde::Registry::Ptr& registry);

 protected:
  /**
   * @brief Construct a new Select Entity object
   * @param props Properties of the select
   */
  SelectContainerTextEntity(std::size_t idx, std::shared_ptr<Registry> registry);

  ~SelectContainerTextEntity() final = default;

  /**
   * @brief Create the select field
   * @param props Properties of the select field
   */
  void OnSpawn(const Select::Properties& props);
};
}  // namespace rtype::client::ui
