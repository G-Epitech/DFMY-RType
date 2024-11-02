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
#include "./select_option_text_entity.hpp"
#include "client/src/systems/ui/select_container.hpp"

using namespace rtype::client::ui;
using namespace zygarde::core::components;
using namespace zygarde::core::types;
using namespace rtype::client::systems::ui;

void Select::Create(const Registry::Ptr& registry, const Select::Properties& props) {
  CreateSelectField(registry, props);
  CreateOptions(registry, props);
}

void Select::CreateSelectField(const Registry::Ptr& registry, const Select::Properties& props) {
  registry->SpawnEntity<SelectContainerEntity>(props);
  registry->SpawnEntity<SelectContainerTextEntity>(props);
}
void Select::RegisterDependencies(const Registry::Ptr& registry) {
  SelectContainerEntity::RegisterDependencies(registry);
  SelectContainerTextEntity::RegisterDependencies(registry);
  SelectOptionEntity::RegisterDependencies(registry);
  SelectOptionTextEntity::RegisterDependencies(registry);
  registry->AddSystem<SelectContainerSystem>();
}

void Select::CreateOptions(const Registry::Ptr& registry, const Select::Properties& props) {
  std::size_t index = 0;

  for (const auto& [value, label] : props.options) {
    registry->SpawnEntity<SelectOptionEntity>(index, props, value, label);
    registry->SpawnEntity<SelectOptionTextEntity>(index, props, value, label);
    index += 1;
  }
}

std::optional<std::string> Select::GetValue(const Registry::Ptr& registry, const std::string& id) {
  auto containers = registry->GetMatchingEntities<SelectContainer>();
  for (auto&& [container] : containers) {
    if (container.selectId == id) {
      return container.selectedOption;
    }
  }
  return std::nullopt;
}
