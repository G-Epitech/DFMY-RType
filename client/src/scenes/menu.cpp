/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** menu.cpp
*/

#include "menu.hpp"

#include "components/drawable.hpp"
#include "components/position.hpp"
#include "systems/drawable.hpp"

using namespace rtype::client;

SceneMenu::SceneMenu(const GlobalContext& context) : SceneBase(context) {
  resourcesManager_.LoadFont("assets/fonts/main.ttf", "main");

  registry_->RegisterComponent<components::Position>();
  registry_->RegisterComponent<components::Drawable>();

  registry_->AddSystem<systems::DrawableSystem>(context.windowManager, resourcesManager_);
}

void SceneMenu::OnActivate() {
  const auto rect = registry_->SpawnEntity();

  registry_->AddComponent<components::Position>(rect, {0, 0});
  registry_->AddComponent<components::Drawable>(
      rect, {components::Rectangle{sf::Color::Red, {1920, 1080}}, {}, components::ViewType::HUD});

  const auto entity = registry_->SpawnEntity();

  registry_->AddComponent<components::Position>(entity, {0, 0});
  registry_->AddComponent<components::Drawable>(
      entity, {components::Text{"Hello World", "main"}, {}, components::ViewType::HUD});
}

void SceneMenu::OnCreate() {}

void SceneMenu::Update(std::chrono::nanoseconds delta_time) {
  registry_->RunSystems();
}
