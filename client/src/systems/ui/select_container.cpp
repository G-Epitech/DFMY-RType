/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select.cpp
*/

#include "./select_container.hpp"

#include "client/src/ui/select/select.hpp"

using namespace rtype::client::ui;
using namespace rtype::client::systems::ui;

void SelectContainerSystem::Run(std::shared_ptr<Registry> r, ZippedComponents components) {
  for (auto&& [drawable, position, container] : components) {
    UpdateOptionsVisibility(r, container);
    AggregateClickPerformed(r, &container);
    if (container.expanded) {
      std::string new_label = container.placeholder;

      UpdateOptionsState(r, container, &new_label);
      UpdateContainerLabel(r, container, new_label);
    }
  }
}

void SelectContainerSystem::UpdateOptionsState(const std::shared_ptr<Registry>& r,
                                               const SelectContainer& container,
                                               std::string* new_label) {
  if (!container.selectedOption || !container.expanded) {
    return;
  }
  auto options = r->GetMatchingEntities<SelectOption, Drawable>();
  for (auto&& [option, drawable] : options) {
    if (option.selectId != container.selectId) {
      continue;
    }
    UpdateOption(container, &option, &drawable);
    if (option.selected) {
      *new_label = option.label;
    }
  }
}
void SelectContainerSystem::UpdateContainerLabel(const std::shared_ptr<Registry>& r,
                                                 const SelectContainer& container,
                                                 const std::string& new_label) {
  auto entities = r->GetMatchingEntities<Drawable, Tags>();

  for (auto&& [drawable, tags] : entities) {
    if (tags & Select::ContainerTextIdTagOf(container.selectId) &&
        std::holds_alternative<Text>(drawable.drawable)) {
      auto& text = std::get<Text>(drawable.drawable);
      text.text = new_label;
    }
  }
}

void SelectContainerSystem::UpdateOption(const SelectContainer& container, SelectOption* option,
                                         Drawable* drawable) {
  option->selected = option->value == (*container.selectedOption);
  drawable->visible = container.expanded;
  if (!std::holds_alternative<Rectangle>(drawable->drawable)) {
    return;
  }
  auto& rect = std::get<Rectangle>(drawable->drawable);
  if (option->selected) {
    rect.fillColor = container.selectedColor;
  } else if (option->hovered) {
    rect.fillColor = container.hoveredColor;
  } else {
    rect.fillColor = container.disabledColor;
  }
}

void SelectContainerSystem::UpdateOptionsVisibility(const std::shared_ptr<Registry>& r,
                                                    const SelectContainer& container) {
  auto options = r->GetMatchingEntities<Drawable, Tags>();
  for (auto&& [drawable, tags] : options) {
    if (tags & Select::OptionIdTagOf(container.selectId)) {
      drawable.visible = container.expanded;
    }
  }
}

void SelectContainerSystem::AggregateClickPerformed(const std::shared_ptr<Registry>& r,
                                                    SelectContainer* container) {
  auto entities = r->GetMatchingEntities<SelectOption>();

  for (auto&& [option] : entities) {
    if (option.selectId != container->selectId) {
      continue;
    }
    container->clickPerformed |= option.clickPerformed;
    option.clickPerformed = false;
  }
  container->expanded = container->clickPerformed;
}
