/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select_entity.cpp
*/

#include "select_container_entity.hpp"

#include <utility>

#include "client/src/components/ui/select.hpp"
#include "libs/mew/src/sets/drawable/drawable.hpp"
#include "libs/zygarde/src/core/components/components.hpp"

using namespace rtype::client::ui;
using namespace rtype::client::components;
using namespace zygarde::core::components;
using namespace mew::sets::drawable;
using namespace mew::sets::events;

SelectContainerEntity::SelectContainerEntity(std::size_t idx, std::shared_ptr<Registry> registry)
    : Entity(idx, std::move(registry)) {}

void SelectContainerEntity::OnSpawn(const Select::Properties& props) {
  std::optional<std::string> selectedOption =
      props.options.empty() ? std::nullopt : std::make_optional(props.options.begin()->second);
  auto aligns = Alignment{HorizontalAlign::kLeft, VerticalAlign::kCenter};
  auto drawable = Rectangle{
      .fillColor = selectedOption ? props.selectedColor : props.disabledColor,
      .outlineColor = sf::Color::White,
      .outlineThickness = 2,
      .size = {props.size.x, props.size.y},
  };

  registry_->AddComponent<SelectContainer>(
      *this, {.expanded = false, .selectedOption = selectedOption, .selectId = props.id});
  registry_->AddComponent<Drawable>(*this, {drawable});
  registry_->AddComponent<Position>(*this, {props.position, aligns});
  registry_->AddComponent<Tags>(*this, Tags({Select::IdTagOf(props.id)}));
  registry_->AddComponent<OnMouseMoved>(
      *this, {.strategy = MouseEventTarget::kAnyTarget,
              .handler = [entity = static_cast<Entity>(*this), props](
                             const sf::Vector2f& pos, const MouseEventTarget& target) mutable {
                return OnHover(entity, props, pos, target);
              }});
}

void SelectContainerEntity::RegisterDependencies(Registry& registry) {
  registry.RegisterComponent<SelectContainer>();
  registry.RegisterComponent<Tags>();
}

void SelectContainerEntity::OnHover(Entity& entity, const Select::Properties& props,
                                    const sf::Vector2f& pos, const MouseEventTarget& target) {
  auto select_container = entity.GetComponent<SelectContainer>();
  auto drawable_component = entity.GetComponent<Drawable>();

  if (!select_container || !drawable_component) {
    return;
  }

  auto& rectangle = std::get<Rectangle>(drawable_component->drawable);

  if (!select_container->selectedOption.has_value()) {
    rectangle.fillColor = props.disabledColor;
  } else if (target == MouseEventTarget::kLocalTarget) {
    rectangle.fillColor = props.hoveredColor;
  } else {
    rectangle.fillColor = props.selectedColor;
  }
}
