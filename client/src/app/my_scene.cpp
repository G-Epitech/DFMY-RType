/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** my_scene.cpp
*/

#include "my_scene.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

#include "my_scene_2.hpp"
#include "scenes/scenes_manager.hpp"

using namespace rtype::client;

MyScene::MyScene(const GlobalContext& global_context) : SceneBase(global_context) {}

void MyScene::Draw() {
  sf::RectangleShape rect(sf::Vector2f(100, 100));
  rect.setFillColor(sf::Color::Red);

  globalContext_.window->draw(rect);
}

void MyScene::Update(std::chrono::nanoseconds delta_time) {
  if (counter_++ == 370) {
    std::cout << "MyScene::Update: will nearly switch to MyScene2" << std::endl;
  }
  if (counter_ > 400) {
    globalContext_.scenesManager->GoToScene<MyScene2>();
    counter_ = 0;
  }
}
