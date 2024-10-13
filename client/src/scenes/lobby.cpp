/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** menu.cpp
*/

#include "lobby.hpp"

#include "components/drawable.hpp"
#include "libs/zygarde/src/core/components/components.hpp"
#include "systems/drawable.hpp"

using namespace rtype::client::scenes;
using namespace rtype::client::systems;
using namespace rtype::client::components;
using namespace zygarde::core::components;
using namespace zygarde::core::types;

SceneLobby::SceneLobby(const GlobalContext& context) : SceneBase(context) {
  resourcesManager_->LoadFont("assets/fonts/main.ttf", "main");
  resourcesManager_->LoadTexture("assets/icons/R-Type.png", "g-epitech-logo");

  registry_->RegisterComponent<Position>();
  registry_->RegisterComponent<Drawable>();
  registry_->RegisterComponent<Tags>();

  registry_->AddSystem<DrawableSystem>(context.windowManager, resourcesManager_);
}

void SceneLobby::OnCreate() {
  CreateGEpitechLogo();
  CreateStatusText();
}

void SceneLobby::OnActivate() {}

void SceneLobby::Update(std::chrono::nanoseconds delta_time) {
  registry_->RunSystems();
}

void SceneLobby::CreateStatusText() {
  const auto main_text = registry_->SpawnEntity();
  const auto secondary_text = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  const auto base =
      Vector3f(context_.windowManager->width_ / 2, context_.windowManager->height_ / 2 + 250);

  registry_->AddComponent<Position>(main_text, {base, aligns});
  registry_->AddComponent<Tags>(main_text, Tags({"main_status_text"}));
  registry_->AddComponent<Drawable>(
      main_text, {Text{"Main Status text", "main", 20}, WindowManager::View::HUD});
  registry_->AddComponent<Position>(secondary_text, {base + Vector3f{0, 50}, aligns});
  registry_->AddComponent<Tags>(secondary_text, Tags({"secondary_status_text"}));
  registry_->AddComponent<Drawable>(
      secondary_text, {Text{"Secondary Status text", "main", 12}, WindowManager::View::HUD});
}
void SceneLobby::CreateGEpitechLogo() {
  const auto logo = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  const auto point = zyc::types::Vector3f(context_.windowManager->width_ / 2,
                                          context_.windowManager->height_ / 2 - 150);
  const auto rect = sf::IntRect{0, 0, 927, 927};
  registry_->AddComponent<Position>(logo, {point, aligns});
  registry_->AddComponent<Drawable>(

      logo,
      {Texture{.name = "g-epitech-logo", .scale = 0.35, .rect = rect}, WindowManager::View::HUD});
}
