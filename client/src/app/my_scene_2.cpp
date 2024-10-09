/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** my_scene.cpp
*/

#include "my_scene_2.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <random>

#include "my_scene.hpp"
#include "scenes/scenes_manager.hpp"
#include "systems/drawable.hpp"
#include "systems/events/key.hpp"
#include "systems/events/mouse/buttons.hpp"
#include "systems/events/mouse/move.hpp"

using namespace rtype::client;

MyScene2::MyScene2(const GlobalContext& context) : SceneBase(context), e(0) {}

void MyScene2::OnCreate() {
  registry_->RegisterComponent<components::OnKeyPressed>();
  registry_->RegisterComponent<components::OnMousePressed>();
  registry_->RegisterComponent<components::OnMouseReleased>();
  registry_->RegisterComponent<components::OnMouseMoved>();
  registry_->RegisterComponent<components::Drawable>();
  registry_->RegisterComponent<components::Position>();
  registry_->AddSystem<KeyPressEventSystem>(context_.windowManager);
  registry_->AddSystem<MousePressEventSystem>(context_.windowManager);
  registry_->AddSystem<MouseMoveEventSystem>(context_.windowManager);
  registry_->AddSystem<DrawableSystem>(context_.windowManager);
  auto entity = registry_->SpawnEntity();
  registry_->AddComponent(entity,
                          components::OnKeyPressed{.handler = [this](sf::Keyboard::Key key) {
                            if (key == sf::Keyboard::Left || key == sf::Keyboard::Right) {
                              context_.scenesManager->GoToScene<MyScene>();
                            }
                          }});
  registry_->AddComponent(
      entity, components::OnMouseMoved{
                  .handler = [this](sf::Vector2f position, events::MouseEventTarget target) {
                    auto drawables = registry_->GetComponents<components::Drawable>();
                    auto& drawable = (*drawables)[0];
                    sf::Image image;
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> dis(0, 254);
                    sf::Color color(dis(gen), dis(gen), dis(gen));
                    if (drawable && target == events::MouseEventTarget::kLocalTarget) {
                      image.create(100, 100, sf::Color::Black);
                    } else {
                      image.create(100, 100, color);
                    }
                    drawable->texture.loadFromImage(image);
                  }});
}

void MyScene2::Update(std::chrono::nanoseconds delta_time) {
  registry_->RunSystems();
}

void MyScene2::OnActivate() {
  sf::Image image;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 254);
  std::uniform_int_distribution<> disPosX(
      0, static_cast<int>(context_.windowManager->window()->getSize().x - 100));
  std::uniform_int_distribution<> disPosY(
      0, static_cast<int>(context_.windowManager->window()->getSize().y - 100));
  sf::Color color(dis(gen), dis(gen), dis(gen));
  image.create(100, 100, color);
  sf::Texture texture;
  texture.loadFromImage(image);
  auto entity = registry_->EntityFromIndex(e);
  registry_->AddComponent(entity, components::Drawable{.texture = texture});
  registry_->AddComponent(entity, components::Position{
                                      .x = static_cast<float>(disPosX(gen)),
                                      .y = static_cast<float>(disPosY(gen)),
                                  });
}
