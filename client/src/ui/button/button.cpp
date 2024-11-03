/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select.cpp
*/

#include "button.hpp"

#include "button_container_entity.hpp"
#include "button_container_text_entity.hpp"

using namespace rtype::client::ui;
using namespace zygarde::core::components;
using namespace zygarde::core::types;
using namespace mew::sets::drawable;

void Button::Create(const Registry::Ptr& registry, const Properties& props) {
  registry->SpawnEntity<ButtonContainerEntity>(props);
  registry->SpawnEntity<ButtonContainerTextEntity>(props);
}

void Button::RegisterDependencies(const Registry::Ptr& registry) {
  ButtonContainerEntity::RegisterDependencies(registry);
}
void Button::SetEnabled(const Registry::Ptr& registry, const std::string& id, bool enabled) {
  auto components = registry->GetMatchingEntities<Tags>();
  for (auto&& [tags] : components) {
    if (tags & IdTagOf(id)) {
      if (enabled && (tags & DisabledTagOf(id))) {
        tags.RemoveTag(DisabledTagOf(id));
      } else if (!enabled && !(tags & DisabledTagOf(id))) {
        tags.AddTag(DisabledTagOf(id));
      }
    }
  }
}
