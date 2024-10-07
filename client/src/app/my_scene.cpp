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
#include "src/systems/events/events.hpp"
#include "systems/drawable.hpp"

using namespace rtype::client;

MyScene::MyScene(const GlobalContext& context) : SceneBase(context), e(0) {}

void MyScene::OnCreate() {
  registry_->RegisterComponent<components::OnKeyPressed>();
  registry_->RegisterComponent<components::Drawable>();
  registry_->RegisterComponent<components::Position>();
  registry_->AddSystem<KeyPressEventSystem>(context_.windowManager);
  registry_->AddSystem<DrawableSystem>(context_.windowManager);
  auto entity = registry_->SpawnEntity();
  registry_->AddComponent(entity,
                          components::OnKeyPressed{.handler = [this](sf::Keyboard::Key key) {
                            if (key == sf::Keyboard::Left || key == sf::Keyboard::Right) {
                              context_.scenesManager->GoToScene<MyScene2>();
                            }
                          }});
  e = static_cast<std::size_t>(entity);
}

void MyScene::Update(std::chrono::nanoseconds delta_time) {
  registry_->RunSystems();
}

void MyScene::OnActivate() {
  sf::Image image;
  // Random color
  sf::Color color(rand() % 255, rand() % 255, rand() % 255);
  image.create(100, 100, color);
  sf::Texture texture;
  texture.loadFromImage(image);
  auto entity = registry_->EntityFromIndex(e);
  registry_->AddComponent(entity, components::Drawable{.texture = texture});
  registry_->AddComponent(
      entity,
      components::Position{
          .x = static_cast<float>(rand() % (context_.windowManager->window()->getSize().x - 100)),
          .y = static_cast<float>(rand() % (context_.windowManager->window()->getSize().y - 100))});
}
