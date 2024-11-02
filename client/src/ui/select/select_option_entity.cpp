/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select_option_entity.cpp
*/

#include "select_option_entity.hpp"

#include <utility>

#include "client/src/components/ui/select.hpp"
#include "libs/mew/src/sets/drawable/drawable.hpp"
#include "libs/mew/src/sets/events/events.hpp"
#include "libs/zygarde/src/core/components/components.hpp"
#include "libs/zygarde/src/core/types/vector/vector.hpp"

using namespace rtype::client::ui;
using namespace rtype::client::components;
using namespace mew::sets::drawable;
using namespace mew::sets::events;
using namespace zygarde::core::components;
using namespace zygarde::core::types;

SelectOptionEntity::SelectOptionEntity(std::size_t idx, std::shared_ptr<Registry> registry)
    : Entity(idx, std::move(registry)) {}

void SelectOptionEntity::RegisterDependencies(const zygarde::Registry::Ptr& registry) {
  registry->RegisterComponent<SelectOption>();
}
void SelectOptionEntity::OnSpawn(std::size_t index, const Select::Properties& props,
                                 const std::string& value, const std::string& label) {
  std::optional<std::string> selected_option = Select::GetDefaultOption(props);
  Rectangle rectangle = {
      .fillColor = sf::Color::Transparent,
      .outlineColor = sf::Color(94, 94, 94),
      .outlineThickness = 1,
      .size = {props.size.x, props.size.y},
  };

  SelectOption option = {
      .label = label,
      .value = value,
      .selected = selected_option && *selected_option == value,
      .selectId = props.id,
  };
  Position position = {
      .point = Vector3f(props.position.x,
                        props.position.y + (static_cast<float>(index + 1) * (props.size.y + 1))),
      .aligns = {HorizontalAlign::kLeft, VerticalAlign::kCenter}};

  registry_->AddComponent<Tags>(*this, Tags({Select::OptionIdTagOf(props.id)}));
  registry_->AddComponent<SelectOption>(*this, option);
  registry_->AddComponent<Drawable>(*this, {
                                               .drawable = rectangle,
                                               .visible = props.expanded,
                                               .layer = 30,
                                           });
  registry_->AddComponent<Position>(*this, position);
  registry_->AddComponent<OnMouseMoved>(
      *this, {.strategy = MouseEventTarget::kAnyTarget,
              .handler = [entity = static_cast<Entity>(*this)](
                             const sf::Vector2f& pos, const MouseEventTarget& target) mutable {
                return OnHover(entity, target);
              }});
  registry_->AddComponent<OnMousePressed>(
      *this, {.strategy = MouseEventTarget::kLocalTarget,
              .handler = [registry = registry_, entity = static_cast<Entity>(*this)](
                             const sf::Mouse::Button& button, const sf::Vector2f& pos,
                             const MouseEventTarget& target) mutable {
                if (button == sf::Mouse::Button::Left) {
                  return OnClick(registry, entity);
                }
              }});
}
void SelectOptionEntity::OnHover(const Entity& entity,
                                 const mew::sets::events::MouseEventTarget& target) {
  auto select_option = entity.GetComponent<SelectOption>();

  if (!select_option) {
    return;
  }
  select_option->hovered = target == MouseEventTarget::kLocalTarget;
}

void SelectOptionEntity::OnClick(const Registry::Ptr& registry, const Entity& entity) {
  auto select_option = entity.GetComponent<SelectOption>();
  auto select_components = registry->GetComponents<SelectContainer>();
  if (!select_option || !select_components) {
    return;
  }
  for (auto& select : *select_components) {
    if (select && select->selectId == select_option->selectId) {
      select->selectedOption = select_option->value;
      select_option->clickPerformed = true;
      break;
    }
  }
}
