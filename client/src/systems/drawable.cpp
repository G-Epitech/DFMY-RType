/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** drawable_system.cpp
*/

#include "drawable.hpp"

#include <utility>

using namespace rtype::client::systems;

DrawableSystem::DrawableSystem(rtype::client::WindowManager::Ptr window_manager,
                               const ResourcesManager& resources_manager)
    : resourcesManager_{resources_manager} {
  windowManager_ = std::move(window_manager);
}

void DrawableSystem::Run(Registry::Ptr r, sparse_array<components::Drawable>::ptr drawables,
                         sparse_array<components::Position>::ptr positions) {
  auto window = windowManager_->window();
  window->clear();
  for (size_t i = 0; i < drawables->size() && i < positions->size(); ++i) {
    if ((*drawables)[i] && (*positions)[i]) {
      auto& drawable = (*drawables)[i].value();
      auto& position = (*positions)[i].value();

      DrawEntity(drawable, position);
    }
  }
  window->display();
}

void DrawableSystem::DrawEntity(const components::Drawable& drawable,
                                const components::Position& position) {
  std::visit(
      [this, position](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, components::Texture>) {
          DrawEntityTexture(arg, position);
        } else if constexpr (std::is_same_v<T, components::Text>) {
          DrawEntityText(arg, position);
        }
      },
      drawable.drawable);
}

void DrawableSystem::DrawEntityTexture(const components::Texture& texture,
                                       const components::Position& position) {
  const auto savedTexture = resourcesManager_.GetTexture(texture.path);

  sprite_.setTexture(savedTexture);
  sprite_.setPosition(position.x, position.y);
  windowManager_->window()->draw(sprite_);
}

void DrawableSystem::DrawEntityText(const components::Text& text,
                                    const components::Position& position) {
  const auto savedFont = resourcesManager_.GetFont(text.fontName);

  text_.setFont(savedFont);
  text_.setString(text.text);
  text_.setCharacterSize(text.characterSize);
  text_.setFillColor(text.color);
  text_.setPosition(position.x, position.y);
  windowManager_->window()->draw(text_);
}
