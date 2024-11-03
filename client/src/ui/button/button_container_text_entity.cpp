/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select_value_entity.cpp
*/

#include "button_container_text_entity.hpp"

#include <utility>

#include "button_container_entity.hpp"
#include "client/src/components/ui/select.hpp"
#include "libs/mew/src/managers/window_manager.hpp"
#include "libs/mew/src/sets/drawable/components/components.hpp"
#include "libs/zygarde/src/core/components/components.hpp"

using namespace mew::managers;
using namespace rtype::client::ui;
using namespace rtype::client::components;
using namespace zygarde::core::components;
using namespace zygarde::core::types;
using namespace mew::sets::drawable;

ButtonContainerTextEntity::ButtonContainerTextEntity(std::size_t idx,
                                                     std::shared_ptr<Registry> registry)
    : Entity(idx, std::move(registry)) {}

void ButtonContainerTextEntity::OnSpawn(const Button::Properties& props) {
  auto position =
      Vector3f(props.position.x + props.size.x * 0.5f, props.position.y - (props.size.y * 0.15f));
  auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};

  auto drawable = Text{.text = props.label,
                       .fontName = props.fontName,
                       .characterSize = static_cast<unsigned int>(props.size.y * 0.5f),
                       .color = sf::Color::White};

  registry_->AddComponent<Drawable>(*this, {drawable});
  registry_->AddComponent<Position>(*this, {position, aligns});
}
