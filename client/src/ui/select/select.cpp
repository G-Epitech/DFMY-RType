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

void Select::Update(const Registry::Ptr& registry, const Select::Properties& props) {
  auto containers_entities = registry->GetMatchingEntities<SelectContainer, Position, Drawable>();
  std::optional<std::size_t> container_index = std::nullopt;

  const auto begin = containers_entities.begin();
  const auto end = containers_entities.end();
  for (auto it = begin; it != end; ++it) {
    auto&& [index, components] = ~it;
    auto&& [container, position, drawable] = components;
    if (container.selectId == props.id) {
      RemoveOldContainer(registry, props, &container);
      container_index = index;
      break;
    }
  }
  if (container_index) {
    registry->KillEntity(registry->EntityFromIndex(*container_index));
  }
  Create(registry, props);
}

void Select::RemoveOldContainer(const Registry::Ptr& registry, const Select::Properties& props,
                                SelectContainer* container) {
  auto options = registry->GetMatchingEntities<Tags>();
  std::list<std::size_t> to_remove;

  const auto begin = options.begin();
  const auto end = options.end();
  for (auto it = begin; it != end; ++it) {
    auto&& [index, components] = ~it;
    auto&& [tags] = components;
    if ((tags & Select::IdTagOf(props.id)) || (tags & Select::OptionIdTagOf(props.id))) {
      to_remove.push_back(index);
    }
  }

  std::for_each(to_remove.begin(), to_remove.end(), [&registry](std::size_t index) {
    registry->KillEntity(registry->EntityFromIndex(index));
  });
}

std::optional<std::string> Select::GetDefaultOption(const Select::Properties& props) {
  std::optional<std::string> selected_option = props.selectedOption;

  if (!selected_option || (selected_option && !props.options.contains(*selected_option))) {
    selected_option =
        props.options.empty() ? std::nullopt : std::make_optional(props.options.begin()->first);
  }
  return selected_option;
}
