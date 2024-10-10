/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** menu.cpp
*/

#include "menu.hpp"

#include "components/drawable.hpp"
#include "components/on_event.hpp"
#include "components/position.hpp"
#include "systems/drawable.hpp"
#include "systems/events/mouse/buttons.hpp"

using namespace rtype::client;

SceneMenu::SceneMenu(const GlobalContext& context) : SceneBase(context) {
  resourcesManager_->LoadFont("assets/fonts/main.ttf", "main");

  registry_->RegisterComponent<components::Position>();
  registry_->RegisterComponent<components::Drawable>();
  registry_->RegisterComponent<components::OnMousePressed>();

  registry_->AddSystem<systems::DrawableSystem>(context.windowManager, resourcesManager_);
  registry_->AddSystem<systems::MousePressEventSystem>(context.windowManager);
}

#include <iostream>
void SceneMenu::OnCreate() {
  const auto title = registry_->SpawnEntity();

  registry_->AddComponent<components::Position>(
      title, {context_.windowManager->width_ / 2, context_.windowManager->height_ / 2 - 250,
              components::HorizontalAlign::CENTER, components::VerticalAlign::CENTER});
  registry_->AddComponent<components::Drawable>(
      title, {components::Text{"R-TYPE", "main", 84}, WindowManager::View::HUD});

  const auto play_button = registry_->SpawnEntity();

  registry_->AddComponent<components::Position>(
      play_button, {context_.windowManager->width_ / 2, context_.windowManager->height_ / 2,
                    components::HorizontalAlign::CENTER, components::VerticalAlign::CENTER});
  registry_->AddComponent<components::Drawable>(
      play_button, {components::Text{"Play", "main", 42}, WindowManager::View::HUD});
  registry_->AddComponent<components::OnMousePressed>(
      play_button,
      components::OnMousePressed{.strategy = events::MouseEventTarget::kLocalTarget,
                                 .handler = [this](sf::Mouse::Button button, sf::Vector2f pos,
                                                   events::MouseEventTarget target) {
                                   std::cout << "Play button pressed" << std::endl;
                                 }});

  const auto settings_button = registry_->SpawnEntity();

  registry_->AddComponent<components::Position>(
      settings_button,
      {context_.windowManager->width_ / 2, context_.windowManager->height_ / 2 + 75,
       components::HorizontalAlign::CENTER, components::VerticalAlign::CENTER});
  registry_->AddComponent<components::Drawable>(
      settings_button, {components::Text{"Settings", "main", 20}, WindowManager::View::HUD});
  registry_->AddComponent<components::OnMousePressed>(
      settings_button,
      components::OnMousePressed{.strategy = events::MouseEventTarget::kLocalTarget,
                                 .handler = [this](sf::Mouse::Button button, sf::Vector2f pos,
                                                   events::MouseEventTarget target) {
                                   std::cout << "Settings button pressed" << std::endl;
                                 }});

  const auto exit_button = registry_->SpawnEntity();

  registry_->AddComponent<components::Position>(
      exit_button, {context_.windowManager->width_ / 2, context_.windowManager->height_ / 2 + 110,
                    components::HorizontalAlign::CENTER, components::VerticalAlign::CENTER});
  registry_->AddComponent<components::Drawable>(
      exit_button, {components::Text{"Exit", "main", 20}, WindowManager::View::HUD});
  registry_->AddComponent<components::OnMousePressed>(
      exit_button,
      components::OnMousePressed{.strategy = events::MouseEventTarget::kLocalTarget,
                                 .handler = [this](const sf::Mouse::Button button, sf::Vector2f pos,
                                                   events::MouseEventTarget target) {
                                   if (button == sf::Mouse::Button::Left) {
                                     context_.scenesManager->Quit();
                                   }
                                 }});
}

void SceneMenu::OnActivate() {}

void SceneMenu::Update(std::chrono::nanoseconds delta_time) {
  registry_->RunSystems();
}
