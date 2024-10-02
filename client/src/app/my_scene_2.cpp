/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** my_scene_2.cpp
*/

#include "my_scene_2.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

#include "my_scene.hpp"
#include "scenes/scenes_manager.hpp"

using namespace rtype::client;

MyScene2::MyScene2(const GlobalContext& global_context) : SceneBase(global_context) {}

void MyScene2::Draw() {
  sf::RectangleShape rect(sf::Vector2f(100, 100));
  rect.setFillColor(sf::Color::Green);

  globalContext_.window->draw(rect);
}

void MyScene2::Update(utils::DeltaTime delta_time) {
  if (counter_++ == 370) {
    std::cout << "MyScene2::Update: will nearly switch to MyScene" << std::endl;
  }

  if (counter_ > 400) {
    globalContext_.scenesManager->GoToScene<MyScene>();
    counter_ = 0;
  }
}
