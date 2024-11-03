/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select_entity.cpp
*/

#include "button_container_entity.hpp"

#include <utility>

#include "client/src/components/ui/select.hpp"
#include "libs/mew/src/managers/window_manager.hpp"
#include "libs/mew/src/sets/drawable/drawable.hpp"
#include "libs/zygarde/src/core/components/components.hpp"

using namespace rtype::client::ui;
using namespace rtype::client::components;
using namespace zygarde::core::components;
using namespace mew::sets::drawable;
using namespace mew::sets::events;
using namespace mew::managers;

ButtonContainerEntity::ButtonContainerEntity(std::size_t idx, std::shared_ptr<Registry> registry)
    : Entity(idx, std::move(registry)) {}

void ButtonContainerEntity::OnSpawn(const Button::Properties& props) {
  auto aligns = Alignment{HorizontalAlign::kLeft, VerticalAlign::kCenter};

  auto drawable = Rectangle{
      .fillColor = props.disabled ? props.disabledColor : props.color,
      .outlineColor = sf::Color::White,
      .outlineThickness = 2,
      .size = {props.size.x, props.size.y},
  };

  registry_->AddComponent<Drawable>(*this, {drawable});
  registry_->AddComponent<Position>(*this, {props.position, aligns});
  registry_->AddComponent<OnMouseMoved>(
      *this, {.strategy = MouseEventTarget::kAnyTarget,
              .handler = [entity = static_cast<Entity>(*this), props](
                             const sf::Vector2f& pos, const MouseEventTarget& target) mutable {
                return OnHover(props, entity, target);
              }});

  registry_->AddComponent<OnMousePressed>(
      *this, {.strategy = MouseEventTarget::kLocalTarget,
              .handler = [entity = static_cast<Entity>(*this), props](
                             const sf::Mouse::Button& button, const sf::Vector2f& pos,
                             const MouseEventTarget& target) mutable {
                return OnClick(props, entity, button, pos, target);
              }});
  auto tags = Tags({});

  if (props.disabled) {
    tags.AddTag(Button::DisabledTagOf(props.id));
  }
  registry_->AddComponent<Tags>(*this, tags);
}

void ButtonContainerEntity::RegisterDependencies(const zygarde::Registry::Ptr& registry) {
  registry->RegisterComponent<Tags>();
}
void ButtonContainerEntity::OnHover(const Button::Properties& props, const Entity& entity,
                                    const MouseEventTarget& target) {
  auto tags = entity.GetComponent<Tags>();
  auto drawable_component = entity.GetComponent<Drawable>();

  if (!tags || !drawable_component) {
    return;
  }

  auto& rectangle = std::get<Rectangle>(drawable_component->drawable);

  if ((*tags) & Button::DisabledTagOf(props.id)) {
    rectangle.fillColor = props.disabledColor;
  } else if (target == MouseEventTarget::kLocalTarget) {
    rectangle.fillColor = props.hoveredColor;
  } else {
    rectangle.fillColor = props.color;
  }
}

void ButtonContainerEntity::OnClick(const Button::Properties& props, const Entity& entity,
                                    const sf::Mouse::Button& button, const sf::Vector2f& pos,
                                    const MouseEventTarget& target) {
  auto tags = entity.GetComponent<Tags>();

  if (!tags) {
    return;
  }
  if ((*tags) & Button::DisabledTagOf(props.id)) {
    return;
  }
  props.action(button, pos, target);
}
