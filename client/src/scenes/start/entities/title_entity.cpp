/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** title_entity.cpp
*/

#include "title_entity.hpp"

#include <utility>

#include "libs/mew/src/sets/drawable/drawable.hpp"
#include "libs/zygarde/src/core/components/position/position.hpp"

using namespace rtype::client::scenes;
using namespace zygarde;
using namespace zygarde::core::types;
using namespace zygarde::core::components;
using namespace mew::sets::drawable;

TitleEntity::TitleEntity(const Entity &other) : Entity(other) {}

TitleEntity::TitleEntity(std::size_t idx, std::shared_ptr<Registry> registry)
    : Entity(idx, std::move(registry)) {}

void TitleEntity::OnSpawn(const std::string &text, Vector3f position, const std::string &fontName,
                          unsigned int characterSize) {
  auto drawable = Text{.text = text,
                       .fontName = fontName,
                       .characterSize = characterSize,
                       .color = sf::Color::White};

  registry_->AddComponent<Drawable>(*this, {.drawable = drawable});
  registry_->AddComponent<Position>(*this,
                                    {
                                        position,
                                        Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter},
                                    });
}
