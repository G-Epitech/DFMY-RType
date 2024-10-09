/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** drawable_system.cpp
*/

#include "drawable.hpp"

#include <utility>

using namespace rtype::client::systems;

DrawableSystem::DrawableSystem(rtype::client::WindowManager::Ptr window_manager) {
  windowManager_ = std::move(window_manager);
}

void DrawableSystem::Run(Registry::Ptr r, sparse_array<components::Drawable>::ptr drawables,
                         sparse_array<components::Position>::ptr positions) {
  auto window = windowManager_->window();
  window->clear();
  for (size_t i = 0; i < drawables->size() && i < positions->size(); ++i) {
    if ((*drawables)[i] && (*positions)[i]) {
      auto &drawable = (*drawables)[i].value();
      auto &position = (*positions)[i].value();

      drawable.bounds = sprite_.getGlobalBounds();
      window->draw(sprite_);
    }
  }
  window->display();
}

void DrawableSystem::DrawEntity(const components::Drawable& drawable, const components::Position& position) {
  std::visit([this, position](auto&& arg) {
    using T = std::decay_t<decltype(arg)>;
    if constexpr (std::is_same_v<T, sf::Texture>) {
      sprite_.setTexture(arg);
      sprite_.setPosition(position.x, position.y);
    } else if constexpr (std::is_same_v<T, sf::Text>) {

    }
  }, drawable.drawable);
}

void DrawableSystem::DrawTexture(const components::Texture& texture, const components::Position& position) {
  auto texture = resourcesManager_.GetTexture(texture.path);
  sprite_.setPosition(position.x, position.y);
}
