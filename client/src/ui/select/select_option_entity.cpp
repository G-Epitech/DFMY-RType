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
#include "libs/zygarde/src/core/components/components.hpp"
#include "libs/zygarde/src/core/types/vector/vector.hpp"

using namespace rtype::client::ui;
using namespace rtype::client::components;
using namespace mew::sets::drawable;
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
      .hovered = false,
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
}
