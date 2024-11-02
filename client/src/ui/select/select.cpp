/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select.cpp
*/

#include "select.hpp"

#include "./select_container_entity.hpp"
#include "./select_container_text_entity.hpp"
#include "./select_option_entity.hpp"

using namespace rtype::client::ui;
using namespace zygarde::core::components;
using namespace zygarde::core::types;

void Select::Create(const Registry::Ptr& registry, const Select::Properties& props) {
  CreateSelectField(registry, props);
  CreateOptions(registry, props);
}
void Select::CreateSelectField(const Registry::Ptr& registry, const Select::Properties& props) {
  registry->SpawnEntity<SelectContainerEntity>(props);
  registry->SpawnEntity<SelectContainerTextEntity>(props);
}
void Select::RegisterDependencies(Registry& registry) {
  SelectContainerEntity::RegisterDependencies(registry);
  SelectOptionEntity::RegisterDependencies(registry);
}

void Select::CreateOptions(const Registry::Ptr& registry, const Select::Properties& props) {
  std::size_t index = 0;

  for (const auto& [value, label] : props.options) {
    std::cout << "Creating option: " << label << std::endl;
    registry->SpawnEntity<SelectOptionEntity>(index++, props, value, label);
  }
}
