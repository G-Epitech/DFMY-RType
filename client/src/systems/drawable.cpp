/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** drawable_system.cpp
*/

#include "drawable.hpp"

#include <iostream>
#include <utility>

namespace zyc = zygarde::core;
using namespace rtype::client::systems;

DrawableSystem::DrawableSystem(WindowManager::Ptr window_manager,
                               std::shared_ptr<ResourcesManager> resources_manager)
    : resourcesManager_{std::move(resources_manager)} {
  windowManager_ = std::move(window_manager);
}

void DrawableSystem::Run(
    Registry::Ptr r,
    zipper<sparse_array<components::Drawable>::ptr, sparse_array<zyc::components::Position>::ptr>
        components) {
  const auto window = windowManager_->window();
  window->clear();
  for (auto&& [drawable, position] : components) {
    windowManager_->SetView(drawable.view);
    DrawEntity(&drawable, position);
  }
  window->display();
}

std::tuple<float, float> DrawableSystem::GetOrigin(const zyc::components::Position& position,
                                                   const sf::FloatRect& bounds) {
  float originX = 0;
  float originY = 0;

  switch (position.aligns.horizontal) {
    case zyc::components::HorizontalAlign::kLeft:
      originX = 0;
      break;
    case zyc::components::HorizontalAlign::kCenter:
      originX = bounds.width / 2;
      break;
    case zyc::components::HorizontalAlign::kRight:
      originX = bounds.width;
      break;
  }

  switch (position.aligns.vertical) {
    case zyc::components::VerticalAlign::kTop:
      originY = 0;
      break;
    case zyc::components::VerticalAlign::kCenter:
      originY = bounds.height / 2;
      break;
    case zyc::components::VerticalAlign::kBottom:
      originY = bounds.height;
      break;
  }

  return {originX, originY};
}

void DrawableSystem::DrawEntity(components::Drawable* drawable,
                                const zyc::components::Position& position) {
  std::visit(
      [this, position, drawable](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        auto shader = windowManager_->GetSelectedShader();
        if constexpr (std::is_same_v<T, components::Texture>) {
          shader->setUniform("objectColor", sf::Glsl::Vec4(1, 1, 1, 1));
          shader->setUniform("hasTexture", true);
          shader->setUniform("texture", sf::Shader::CurrentTexture);
          DrawEntityTexture(arg, position, *shader);
          drawable->bounds = sprite_.getGlobalBounds();
        } else if constexpr (std::is_same_v<T, components::Text>) {
          shader->setUniform("objectColor", sf::Glsl::Vec4(arg.color));
          shader->setUniform("hasTexture", true);
          shader->setUniform("texture", sf::Shader::CurrentTexture);
          DrawEntityText(arg, position, *shader);
          drawable->bounds = text_.getGlobalBounds();
        } else if constexpr (std::is_same_v<T, components::Rectangle>) {
          shader->setUniform("objectColor", sf::Glsl::Vec4(arg.color));
          shader->setUniform("hasTexture", false);
          DrawEntityRectangle(arg, position, *shader);
          drawable->bounds = shape_.getGlobalBounds();
        }
      },
      drawable->drawable);
}

void DrawableSystem::DrawEntityTexture(const components::Texture& texture,
                                       const zyc::components::Position& position,
                                       const sf::Shader& shader) {
  const auto saved_texture = resourcesManager_->GetTexture(texture.name);

  sprite_.setScale(1, 1);
  sprite_.setTexture(*saved_texture);
  sprite_.setTextureRect(texture.rect);
  sprite_.setPosition(position.point.x, position.point.y);

  const auto origin = GetOrigin(position, sprite_.getGlobalBounds());
  sprite_.setOrigin(std::get<0>(origin), std::get<1>(origin));

  sprite_.setScale(texture.scale, texture.scale);
  windowManager_->window()->draw(sprite_, &shader);
}

void DrawableSystem::DrawEntityText(const components::Text& text,
                                    const zyc::components::Position& position,
                                    const sf::Shader& shader) {
  const auto saved_font = resourcesManager_->GetFont(text.fontName);

  text_.setFont(*saved_font);
  text_.setString(text.text);
  text_.setStyle(text.style);
  text_.setCharacterSize(text.characterSize);
  text_.setFillColor(text.color);
  text_.setPosition(position.point.x, position.point.y);

  text_.setOutlineColor(text.color);
  text_.setOutlineThickness(text.style == sf::Text::Style::Underlined ? 1 : 0);

  const auto origin = GetOrigin(position, text_.getGlobalBounds());
  text_.setOrigin(std::get<0>(origin), std::get<1>(origin));

  windowManager_->window()->draw(text_, &shader);
}

void DrawableSystem::DrawEntityRectangle(const components::Rectangle& rectangle,
                                         const zyc::components::Position& position,
                                         const sf::Shader& shader) {
  shape_.setFillColor(rectangle.color);
  shape_.setSize(rectangle.size);
  shape_.setPosition(position.point.x, position.point.y);

  const auto origin = GetOrigin(position, shape_.getGlobalBounds());
  shape_.setOrigin(std::get<0>(origin), std::get<1>(origin));

  windowManager_->window()->draw(shape_, &shader);
}
