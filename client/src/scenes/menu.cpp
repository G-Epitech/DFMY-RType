/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** my_scene.cpp
*/

#include "menu.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

using namespace rtype::client;

SceneMenu::SceneMenu(const GlobalContext& context) : SceneBase(context) {}

void SceneMenu::Draw() {
  sf::RectangleShape rect(sf::Vector2f(100, 100));
  rect.setFillColor(sf::Color::Red);

  context_.window->draw(rect);
}

void SceneMenu::Update(std::chrono::nanoseconds delta_time) {

}
