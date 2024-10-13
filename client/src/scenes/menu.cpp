/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** menu.cpp
*/

#include "menu.hpp"

#include "components/drawable.hpp"
#include "components/on_event.hpp"
#include "game.hpp"
#include "libs/zygarde/src/core/components/components.hpp"
#include "lobby.hpp"
#include "settings.hpp"
#include "systems/drawable.hpp"
#include "systems/events/mouse/buttons.hpp"
#include "systems/events/mouse/move.hpp"

using namespace rtype::client::scenes;
using namespace rtype::client::systems;
using namespace rtype::client::components;
using namespace zyc::components;
using namespace zyc::types;

SceneMenu::SceneMenu(const GlobalContext& context) : SceneBase(context) {
  resourcesManager_->LoadFont("assets/fonts/main.ttf", "main");

  registry_->RegisterComponent<Position>();
  registry_->RegisterComponent<Drawable>();
  registry_->RegisterComponent<OnMousePressed>();
  registry_->RegisterComponent<OnMouseMoved>();
  registry_->RegisterComponent<Tags>();

  registry_->AddSystem<systems::DrawableSystem>(context.windowManager, resourcesManager_);
  registry_->AddSystem<systems::MousePressEventSystem>(context.windowManager);
  registry_->AddSystem<systems::MouseMoveEventSystem>(context.windowManager);
}

void SceneMenu::OnCreate() {
  CreateTitle();
  CreatePlayButton();
  CreateSettingsButton();
  CreateExitButton();
  CreateServerConnectionLabel();
}

void SceneMenu::OnActivate() {
  context_.serverConnectionManager->ConnectAsync();
}

void SceneMenu::Update(std::chrono::nanoseconds delta_time) {
  UpdateConnectionLabel();
  registry_->RunSystems();
}

void SceneMenu::CreateTitle() const {
  const auto title = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  const auto point = zyc::types::Vector3f(context_.windowManager->width_ / 2,
                                          context_.windowManager->height_ / 2 - 250);

  registry_->AddComponent<Position>(title, {point, aligns});
  registry_->AddComponent<Drawable>(title, {Text{"R-TYPE", "main", 84}, WindowManager::View::HUD});
}

void SceneMenu::CreatePlayButton() const {
  const auto play_button = registry_->SpawnEntity();
  const auto point =
      zyc::types::Vector3f(context_.windowManager->width_ / 2, context_.windowManager->height_ / 2);
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(play_button, {point, aligns});
  registry_->AddComponent<Drawable>(play_button,
                                    {Text{"Play", "main", 42}, WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      play_button,
      OnMousePressed{.strategy = events::MouseEventTarget::kLocalTarget,
                     .handler = [this](const sf::Mouse::Button& button, const sf::Vector2f& pos,
                                       const events::MouseEventTarget& target) {
                       if (button == sf::Mouse::Button::Left &&
                           context_.serverConnectionManager->Connected()) {
                         context_.scenesManager->GoToScene<SceneLobby>();
                       }
                     }});
  registry_->AddComponent<OnMouseMoved>(
      play_button,
      OnMouseMoved{.strategy = events::MouseEventTarget::kAnyTarget,
                   .handler = [this, play_button](const sf::Vector2f& pos,
                                                  const events::MouseEventTarget& target) {
                     auto drawables = registry_->GetComponents<Drawable>();

                     auto& dr = (*drawables)[static_cast<std::size_t>(play_button)];

                     if (dr) {
                       auto& drawable = dr.value();
                       auto& variant = drawable.drawable;

                       if (std::holds_alternative<Text>(variant)) {
                         auto& text = std::get<Text>(variant);
                         if (target == events::MouseEventTarget::kLocalTarget) {
                           text.style = sf::Text::Style::Underlined;
                         } else {
                           text.style = sf::Text::Style::Regular;
                         }
                       }
                     }
                   }});
}

void SceneMenu::CreateSettingsButton() const {
  const auto settings_button = registry_->SpawnEntity();
  const auto point = zyc::types::Vector3f(context_.windowManager->width_ / 2,
                                          context_.windowManager->height_ / 2 + 75);
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(settings_button, {point, aligns});
  registry_->AddComponent<Drawable>(settings_button,
                                    {Text{"Settings", "main", 20}, WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      settings_button,
      OnMousePressed{.strategy = events::MouseEventTarget::kLocalTarget,
                     .handler = [this](const sf::Mouse::Button& button, const sf::Vector2f& pos,
                                       const events::MouseEventTarget& target) {
                       if (button == sf::Mouse::Button::Left) {
                         context_.scenesManager->GoToScene<SceneSettings>();
                       }
                     }});
  registry_->AddComponent<OnMouseMoved>(
      settings_button,
      OnMouseMoved{.strategy = events::MouseEventTarget::kAnyTarget,
                   .handler = [this, settings_button](const sf::Vector2f& pos,
                                                      const events::MouseEventTarget& target) {
                     auto drawables = registry_->GetComponents<Drawable>();

                     auto& dr = (*drawables)[static_cast<std::size_t>(settings_button)];

                     if (dr) {
                       auto& drawable = dr.value();
                       auto& variant = drawable.drawable;

                       if (std::holds_alternative<Text>(variant)) {
                         auto& text = std::get<Text>(variant);
                         if (target == events::MouseEventTarget::kLocalTarget) {
                           text.style = sf::Text::Style::Underlined;
                         } else {
                           text.style = sf::Text::Style::Regular;
                         }
                       }
                     }
                   }});
}

void SceneMenu::CreateExitButton() const {
  const auto exit_button = registry_->SpawnEntity();
  const auto point = zyc::types::Vector3f(context_.windowManager->width_ / 2,
                                          context_.windowManager->height_ / 2 + 110);
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  registry_->AddComponent<Position>(exit_button, {point, aligns});
  registry_->AddComponent<Drawable>(exit_button,
                                    {Text{"Exit", "main", 20}, WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      exit_button,
      OnMousePressed{.strategy = events::MouseEventTarget::kLocalTarget,
                     .handler = [this](const sf::Mouse::Button& button, const sf::Vector2f& pos,
                                       events::MouseEventTarget target) {
                       if (button == sf::Mouse::Button::Left) {
                         context_.scenesManager->Quit();
                       }
                     }});
  registry_->AddComponent<OnMouseMoved>(
      exit_button,
      OnMouseMoved{.strategy = events::MouseEventTarget::kAnyTarget,
                   .handler = [this, exit_button](const sf::Vector2f& pos,
                                                  const events::MouseEventTarget& target) {
                     auto drawables = registry_->GetComponents<Drawable>();

                     auto& dr = (*drawables)[static_cast<std::size_t>(exit_button)];

                     if (dr) {
                       auto& drawable = dr.value();
                       auto& variant = drawable.drawable;

                       if (std::holds_alternative<Text>(variant)) {
                         auto& text = std::get<Text>(variant);
                         if (target == events::MouseEventTarget::kLocalTarget) {
                           text.style = sf::Text::Style::Underlined;
                         } else {
                           text.style = sf::Text::Style::Regular;
                         }
                       }
                     }
                   }});
}

void SceneMenu::CreateServerConnectionLabel() const {
  const auto label = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  const auto point =
      Vector3f(context_.windowManager->width_ / 2, context_.windowManager->height_ - 100);

  registry_->AddComponent<Position>(label, {point, aligns});
  registry_->AddComponent<Tags>(label, Tags({"connection_label"}));
  registry_->AddComponent<Drawable>(label, {Text{.text = GetConnectionLabelText(),
                                                 .fontName = "main",
                                                 .characterSize = 13,
                                                 .color = GetConnectionLabelColor()},
                                            WindowManager::View::HUD});
}
sf::Color SceneMenu::GetConnectionLabelColor() const {
  if (context_.serverConnectionManager->Connected()) {
    return {3, 138, 10, 255};
  } else {
    return {0, 93, 140, 255};
  }
}
std::string SceneMenu::GetConnectionLabelText() const {
  if (context_.serverConnectionManager->Connected()) {
    return "Connected to server";
  } else {
    return "Connecting to server. Please wait.";
  }
}
void SceneMenu::UpdateConnectionLabel() const {
  auto drawables = registry_->GetComponents<Drawable>();
  auto labels = registry_->GetComponents<Tags>();
  std::size_t entity_id = 0;

  for (auto& label : *labels) {
    if (label && ((*label) & "connection_label"))
      break;
    entity_id += 1;
  }
  if (entity_id >= labels->size())
    return;
  auto& drawable = (*drawables)[entity_id];
  auto& text = std::get<Text>(drawable->drawable);
  text.text = GetConnectionLabelText();
  text.color = GetConnectionLabelColor();
}
