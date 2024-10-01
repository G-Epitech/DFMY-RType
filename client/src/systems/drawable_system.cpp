/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** drawable_system.cpp
*/

#include "drawable_system.hpp"

using namespace rtype::client::systems;

DrawableSystem::DrawableSystem(const std::shared_ptr<sf::RenderWindow>& window) : window_(window) {}

void DrawableSystem::Run(Registry* r, sparse_array<components::Drawable>& drawables,
                         sparse_array<components::Position>& positions) {
  window_->clear();
  for (size_t i = 0; i < drawables.size() && i < positions.size(); ++i) {
    if (drawables[i] && positions[i]) {
      const auto [texture] = drawables[i].value();
      const auto [x, y] = positions[i].value();

      sprite_.setTexture(texture);
      sprite_.setPosition(x, y);
      window_->draw(sprite_);
    }
  }
  window_->display();
}
