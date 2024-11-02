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
      props.options.empty() ? std::nullopt : std::make_optional(props.options.begin()->first);
  auto aligns = Alignment{HorizontalAlign::kLeft, VerticalAlign::kCenter};
  auto drawable = Rectangle{
      .fillColor = selectedOption ? props.selectedColor : props.disabledColor,
      .outlineColor = sf::Color::White,
      .outlineThickness = 2,
      .size = {props.size.x, props.size.y},
  };

  registry_->AddComponent<SelectContainer>(*this, {
                                                      .expanded = false,
                                                      .selectedOption = selectedOption,
                                                      .selectId = props.id,
                                                      .placeholder = props.placeholder,
                                                      .selectedColor = props.selectedColor,
                                                      .disabledColor = props.disabledColor,
                                                      .hoveredColor = props.hoveredColor,
                                                  });
  registry_->AddComponent<Drawable>(*this, {drawable});
  registry_->AddComponent<Position>(*this, {props.position, aligns});
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

void SelectContainerEntity::RegisterDependencies(Registry& registry) {
  registry.RegisterComponent<SelectContainer>();
  registry.RegisterComponent<Tags>();
}

void SelectContainerEntity::OnHover(Entity& entity, const MouseEventTarget& target) {
  auto select_container = entity.GetComponent<SelectContainer>();
  auto drawable_component = entity.GetComponent<Drawable>();

  if (!select_container || !drawable_component) {
    return;
  }

  auto& rectangle = std::get<Rectangle>(drawable_component->drawable);

  if (!select_container->selectedOption.has_value()) {
    rectangle.fillColor = select_container->disabledColor;
  } else if (target == MouseEventTarget::kLocalTarget) {
    rectangle.fillColor = select_container->hoveredColor;
  } else {
    rectangle.fillColor = select_container->selectedColor;
  }
}
void SelectContainerEntity::OnClick(const Registry::Ptr& registry, Entity& entity) {
  auto select_container = entity.GetComponent<SelectContainer>();

  if (!select_container || select_container->expanded ||
      !select_container->selectedOption.has_value()) {
    return;
  }
  FoldAllOtherSelects(registry, select_container->selectId);
  select_container->expanded = true;
  std::cout << "Select " << select_container->selectId << " expanded" << std::endl;
}

void SelectContainerEntity::FoldAllOtherSelects(const Registry::Ptr& registry,
                                                const std::string& id) {
  auto select_containers = registry->GetComponents<SelectContainer>();

  for (auto& select_container : *select_containers) {
    if (!select_container || select_container->selectId == id) {
      continue;
    }
    std::cout << "Select " << select_container->selectId << " folded" << std::endl;
    select_container->expanded = false;
  }
}
