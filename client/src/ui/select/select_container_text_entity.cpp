/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select_value_entity.cpp
*/

#include "select_container_text_entity.hpp"

#include <utility>

#include "client/src/components/ui/select.hpp"
#include "libs/mew/src/sets/drawable/components/components.hpp"
#include "libs/zygarde/src/core/components/components.hpp"
#include "select_container_entity.hpp"

using namespace rtype::client::ui;
using namespace rtype::client::components;
using namespace zygarde::core::components;
using namespace zygarde::core::types;
using namespace mew::sets::drawable;

SelectContainerTextEntity::SelectContainerTextEntity(std::size_t idx,
                                                     std::shared_ptr<Registry> registry)
    : Entity(idx, std::move(registry)) {}

void SelectContainerTextEntity::OnSpawn(const Select::Properties& props) {
  auto label = props.options.empty() ? props.placeholder : props.options.begin()->second;
  auto position =
      Vector3f(props.position.x + props.size.x * 0.5f, props.position.y - (props.size.y * 0.15f));
  auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};

  auto drawable =
      Text{.text = label,
           .fontName = "main",
           .characterSize = static_cast<unsigned int>(props.size.y * 0.5f),
           .style = props.options.empty() ? sf::Text::Style::Italic : sf::Text::Style::Regular,
           .color = sf::Color::White};

  registry_->AddComponent<Drawable>(*this, {drawable});
  registry_->AddComponent<Position>(*this, {position, aligns});
  registry_->AddComponent<Tags>(
      *this, Tags({Select::ContainerTextIdTagOf(props.id), Select::IdTagOf(props.id)}));
}

void SelectContainerTextEntity::RegisterDependencies(const zygarde::Registry::Ptr& registry) {
  registry->RegisterComponent<Tags>();
}
