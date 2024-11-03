/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** title_entity.cpp
*/

#include "text_entity.hpp"

#include <utility>

#include "libs/mew/src/sets/drawable/drawable.hpp"
#include "libs/zygarde/src/core/components/position/position.hpp"

using namespace rtype::client::scenes;
using namespace zygarde;
using namespace zygarde::core::types;
using namespace zygarde::core::components;
using namespace mew::sets::drawable;
using namespace mew::managers;

TextEntity::TextEntity(const Entity &other) : Entity(other) {}

TextEntity::TextEntity(std::size_t idx, std::shared_ptr<Registry> registry)
    : Entity(idx, std::move(registry)) {}

void TextEntity::OnSpawn(const TextEntity::Properties &props) {
  auto drawable = Text{.text = props.text,
                       .fontName = props.fontName,
                       .characterSize = props.characterSize,
                       .style = props.style,
                       .color = props.color};

  registry_->AddComponent<Drawable>(
      *this, {.drawable = drawable, .view = WindowManager::HUD, .visible = props.visible});
  registry_->AddComponent<Position>(*this, {
                                               props.position,
                                               props.alignment,
                                           });
  auto tags = Tags({});
  for (const auto &tag : props.tags) {
    tags.AddTag(tag);
  }
  registry_->AddComponent<Tags>(*this, tags);
}

void TextEntity::RegisterDependencies(const Registry::Ptr &registry) {
  registry->RegisterComponent<Drawable>();
  registry->RegisterComponent<Position>();
  registry->RegisterComponent<Tags>();
}
