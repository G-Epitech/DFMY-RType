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

void DrawableSystem::Run(Registry::Ptr r, sparse_array<components::Drawable>& drawables,
                         sparse_array<components::Position>& positions) {
  auto window = windowManager_->window();
  window->clear();
  for (size_t i = 0; i < drawables.size() && i < positions.size(); ++i) {
    if (drawables[i] && positions[i]) {
      const auto [texture] = drawables[i].value();
      const auto [x, y] = positions[i].value();

      sprite_.setTexture(texture);
      sprite_.setPosition(x, y);
      window->draw(sprite_);
    }
  }
  window->display();
}
