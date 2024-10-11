/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** drawable_system.cpp
*/

#include "drawable.hpp"

#include <utility>

using namespace rtype::client::systems;

DrawableSystem::DrawableSystem(WindowManager::Ptr window_manager,
                               std::shared_ptr<ResourcesManager> resources_manager)
    : resourcesManager_{std::move(resources_manager)} {
  windowManager_ = std::move(window_manager);
}

void DrawableSystem::Run(Registry::Ptr r, sparse_array<components::Drawable>::ptr drawables,
                         sparse_array<components::Position>::ptr positions) {
  const auto window = windowManager_->window();
  window->clear();
  for (size_t i = 0; i < drawables->size() && i < positions->size(); ++i) {
    if ((*drawables)[i] && (*positions)[i]) {
      const auto drawable = &((*drawables)[i].value());
      auto position = (*positions)[i].value();

      windowManager_->SetView(drawable->view);
      DrawEntity(drawable, position);
    }
  }
  window->display();
}

std::tuple<float, float> DrawableSystem::GetOrigin(const components::Position& position,
                                                   const sf::FloatRect& bounds) {
  float originX = 0;
  float originY = 0;

  switch (position.horizontalAlign) {
    case components::HorizontalAlign::kLeft:
      originX = 0;
      break;
    case components::HorizontalAlign::kCenter:
      originX = bounds.width / 2;
      break;
    case components::HorizontalAlign::kRight:
      originX = bounds.width;
      break;
  }

  switch (position.verticalAlign) {
    case components::VerticalAlign::kTop:
      originY = 0;
      break;
    case components::VerticalAlign::kCenter:
      originY = bounds.height / 2;
      break;
    case components::VerticalAlign::kBottom:
      originY = bounds.height;
      break;
  }

  return {originX, originY};
}

void DrawableSystem::DrawEntity(components::Drawable* drawable,
                                const components::Position& position) {
  std::visit(
      [this, position, drawable](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, components::Texture>) {
          DrawEntityTexture(arg, position);
          drawable->bounds = sprite_.getGlobalBounds();
        } else if constexpr (std::is_same_v<T, components::Text>) {
          DrawEntityText(arg, position);
          drawable->bounds = text_.getGlobalBounds();
        } else if constexpr (std::is_same_v<T, components::Rectangle>) {
          DrawEntityRectangle(arg, position);
          drawable->bounds = shape_.getGlobalBounds();
        }
      },
      drawable->drawable);
}

void DrawableSystem::DrawEntityTexture(const components::Texture& texture,
                                       const components::Position& position) {
  const auto savedTexture = resourcesManager_->GetTexture(texture.path);

  sprite_.setScale(1, 1);
  sprite_.setTexture(*savedTexture);
  sprite_.setTextureRect(texture.rect);
  sprite_.setPosition(position.x, position.y);

  const auto origin = GetOrigin(position, sprite_.getGlobalBounds());
  sprite_.setOrigin(std::get<0>(origin), std::get<1>(origin));

  sprite_.setScale(texture.scale, texture.scale);
  windowManager_->window()->draw(sprite_);
}

void DrawableSystem::DrawEntityText(const components::Text& text,
                                    const components::Position& position) {
  const auto savedFont = resourcesManager_->GetFont(text.fontName);

  text_.setFont(*savedFont);
  text_.setString(text.text);
  text_.setStyle(text.style);
  text_.setCharacterSize(text.characterSize);
  text_.setFillColor(text.color);
  text_.setPosition(position.x, position.y);

  text_.setOutlineColor(text.color);
  text_.setOutlineThickness(text.style == sf::Text::Style::Underlined ? 1 : 0);

  const auto origin = GetOrigin(position, text_.getGlobalBounds());
  text_.setOrigin(std::get<0>(origin), std::get<1>(origin));

  windowManager_->window()->draw(text_);
}

void DrawableSystem::DrawEntityRectangle(const components::Rectangle& rectangle,
                                         const components::Position& position) {
  shape_.setFillColor(rectangle.color);
  shape_.setSize(rectangle.size);
  shape_.setPosition(position.x, position.y);

  const auto origin = GetOrigin(position, shape_.getGlobalBounds());
  shape_.setOrigin(std::get<0>(origin), std::get<1>(origin));

  windowManager_->window()->draw(shape_);
}
