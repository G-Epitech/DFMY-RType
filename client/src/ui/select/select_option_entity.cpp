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

void SelectOptionEntity::RegisterDependencies(Registry& registry) {
  registry.RegisterComponent<SelectOption>();
}
void SelectOptionEntity::OnSpawn(std::size_t index, const Select::Properties& props,
                                 const std::string& value, const std::string& label) {
  Rectangle rectangle = {
      .fillColor = sf::Color::Transparent,
      .outlineColor = sf::Color(94, 94, 94),
      .outlineThickness = 1,
      .size = {props.size.x, props.size.y},
  };

  SelectOption option = {
      .label = label,
      .value = value,
      .selected = false,
      .selectId = props.id,
  };
  Position position = {
      .point = Vector3f(props.position.x,
                        props.position.y + (static_cast<float>(index + 1) * (props.size.y + 1))),
      .aligns = {HorizontalAlign::kLeft, VerticalAlign::kCenter}};

  registry_->AddComponent<SelectOption>(*this, option);
  registry_->AddComponent<Drawable>(*this, {
                                               .drawable = rectangle,
                                               .visible = true,
                                               .layer = 30,
                                           });
  registry_->AddComponent<Position>(*this, position);
  registry_->AddComponent<OnMouseMoved>(
      *this, {.strategy = MouseEventTarget::kAnyTarget,
              .handler = [entity = static_cast<Entity>(*this), props](
                             const sf::Vector2f& pos, const MouseEventTarget& target) mutable {
                return OnHover(entity, props, target);
              }});
}
void SelectOptionEntity::OnHover(Entity& entity, const Select::Properties& props,
                                 const mew::sets::events::MouseEventTarget& target) {
  auto drawable_component = entity.GetComponent<Drawable>();
  auto select_option = entity.GetComponent<SelectOption>();

  if (!select_option || !drawable_component ||
      !std::holds_alternative<Rectangle>(drawable_component->drawable)) {
    return;
  }
  auto& rectangle = std::get<Rectangle>(drawable_component->drawable);

  if (target == MouseEventTarget::kLocalTarget) {
    rectangle.fillColor = props.hoveredColor;
  } else if (select_option->selected) {
    rectangle.fillColor = props.selectedColor;
  } else {
    rectangle.fillColor = props.disabledColor;
  }
}
