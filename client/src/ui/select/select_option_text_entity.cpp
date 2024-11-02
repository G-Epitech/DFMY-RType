/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select_option_entity.cpp
*/

#include "select_option_text_entity.hpp"

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

SelectOptionTextEntity::SelectOptionTextEntity(std::size_t idx, std::shared_ptr<Registry> registry)
    : Entity(idx, std::move(registry)) {}

void SelectOptionTextEntity::OnSpawn(std::size_t index, const Select::Properties& props,
                                     const std::string& label) {
  Position position = {
      .point = Vector3f(props.position.x + props.size.x * 0.5f,
                        props.position.y + (static_cast<float>(index + 1) * (props.size.y + 1) -
                                            (props.size.y * 0.15f))),
      .aligns = {HorizontalAlign::kCenter, VerticalAlign::kCenter}};

  auto drawable = Text{.text = label,
                       .fontName = "main",
                       .characterSize = static_cast<unsigned int>(props.size.y * 0.5f),
                       .color = sf::Color::White};

  registry_->AddComponent<Drawable>(*this, {drawable});
  registry_->AddComponent<Position>(*this, position);
}
