/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** menu.cpp
*/

#include "menu.hpp"

#include "./start/start.hpp"
#include "leaderboard.hpp"
#include "libs/mew/src/sets/drawable/drawable.hpp"
#include "libs/mew/src/sets/events/events.hpp"
#include "lobby.hpp"
#include "settings.hpp"
#include "systems/blink.hpp"
#include "systems/utils/input_cursor.hpp"
#include "utils/input.hpp"

using namespace rtype::client::scenes;
using namespace rtype::client::services;
using namespace mew::sets::drawable;
using namespace mew::sets::events;
using namespace mew::managers;
using namespace zygarde::core::components;
using namespace zygarde::core::types;

SceneMenu::SceneMenu(DependenciesHandler::Ptr services) : SceneBase(std::move(services)) {
  registry_->RegisterComponent<Tags>();
  registry_->AddSystem<systems::BlinkSystem>();
  registry_->AddSystem<systems::utils::input::CursorSystem>();
  serverConnectionService_ = services_->GetOrThrow<ServerConnectionService>();
}

void SceneMenu::OnCreate() {
  CreateTitle();
  CreatePlayButton();
  CreateLeaderboardButton();
  CreateSettingsButton();
  CreateExitButton();
  CreateServerConnectionLabel();
  utils::Input::Create(registry_, "username",
                       Vector3f{managers_.window->GetWidth() / 2, managers_.window->GetHeight() / 2 + 150},
                       {HorizontalAlign::kCenter, VerticalAlign::kCenter});
}

void SceneMenu::OnActivate() {
  serverConnectionService_->ConnectAsync();
}

void SceneMenu::Update(DeltaTime delta_time) {
  UpdateConnectionLabel();
  registry_->RunSystems();
}

void SceneMenu::CreateTitle() const {
  const auto title = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  const auto point =
      Vector3f(managers_.window->GetWidth() / 2, managers_.window->GetHeight() / 2 - 250);

  registry_->AddComponent<Position>(title, {point, aligns});
  registry_->AddComponent<Drawable>(title, {Text{"R-TYPE", "main", 84}, WindowManager::View::HUD});
}

void SceneMenu::CreatePlayButton() const {
  const auto play_button = registry_->SpawnEntity();
  const auto point = Vector3f(managers_.window->GetWidth() / 2, managers_.window->GetHeight() / 2);
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(play_button, {point, aligns});
  registry_->AddComponent<Drawable>(play_button,
                                    {Text{"Play", "main", 42}, WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      play_button,
      OnMousePressed{.strategy = MouseEventTarget::kLocalTarget,
                     .handler = [this](const sf::Mouse::Button& button, const sf::Vector2f& pos,
                                       const MouseEventTarget& target) {
                       if (button == sf::Mouse::Button::Left &&
                           serverConnectionService_->Connected()) {
                         managers_.scenes->GoToScene<SceneStart>();
                       }
                     }});
  registry_->AddComponent<OnMouseMoved>(
      play_button, OnMouseMoved{.strategy = MouseEventTarget::kAnyTarget,
                                .handler = [this, play_button](const sf::Vector2f& pos,
                                                               const MouseEventTarget& target) {
                                  auto drawables = registry_->GetComponents<Drawable>();

                                  auto& dr = (*drawables)[static_cast<std::size_t>(play_button)];

                                  if (dr) {
                                    auto& drawable = dr.value();
                                    auto& variant = drawable.drawable;

                                    if (std::holds_alternative<Text>(variant)) {
                                      auto& text = std::get<Text>(variant);
                                      if (target == MouseEventTarget::kLocalTarget) {
                                        text.style = sf::Text::Style::Underlined;
                                      } else {
                                        text.style = sf::Text::Style::Regular;
                                      }
                                    }
                                  }
                                }});
}

void SceneMenu::CreateLeaderboardButton() const {
  const auto leaderboard_button = registry_->SpawnEntity();
  const auto point = Vector3f(managers_.window->GetWidth() / 2, managers_.window->GetHeight() / 2 + 75);
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(leaderboard_button, {point, aligns});
  registry_->AddComponent<Drawable>(leaderboard_button,
                                    {Text{"Leaderboard", "main", 20}, WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      leaderboard_button,
      OnMousePressed{.strategy = MouseEventTarget::kLocalTarget,
                     .handler = [this](const sf::Mouse::Button& button, const sf::Vector2f& pos,
                                       const MouseEventTarget& target) {
                       if (button == sf::Mouse::Button::Left) {
                         managers_.scenes->GoToScene<SceneLeaderboard>();
                       }
                     }});
  registry_->AddComponent<OnMouseMoved>(
      leaderboard_button,
      OnMouseMoved{.strategy = MouseEventTarget::kAnyTarget,
                   .handler = [this, leaderboard_button](const sf::Vector2f& pos,
                                                         const MouseEventTarget& target) {
                     auto drawables = registry_->GetComponents<Drawable>();

                     auto& dr = (*drawables)[static_cast<std::size_t>(leaderboard_button)];

                     if (dr) {
                       auto& drawable = dr.value();
                       auto& variant = drawable.drawable;

                       if (std::holds_alternative<Text>(variant)) {
                         auto& text = std::get<Text>(variant);
                         if (target == MouseEventTarget::kLocalTarget) {
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
  const auto point =
      Vector3f(managers_.window->GetWidth() / 2, managers_.window->GetHeight() / 2 + 75);
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(settings_button, {point, aligns});
  registry_->AddComponent<Drawable>(settings_button,
                                    {Text{"Settings", "main", 20}, WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      settings_button,
      OnMousePressed{.strategy = MouseEventTarget::kLocalTarget,
                     .handler = [this](const sf::Mouse::Button& button, const sf::Vector2f& pos,
                                       const MouseEventTarget& target) {
                       if (button == sf::Mouse::Button::Left) {
                         managers_.scenes->GoToScene<SceneSettings>();
                       }
                     }});
  registry_->AddComponent<OnMouseMoved>(
      settings_button,
      OnMouseMoved{.strategy = MouseEventTarget::kAnyTarget,
                   .handler = [this, settings_button](const sf::Vector2f& pos,
                                                      const MouseEventTarget& target) {
                     auto drawables = registry_->GetComponents<Drawable>();

                     auto& dr = (*drawables)[static_cast<std::size_t>(settings_button)];

                     if (dr) {
                       auto& drawable = dr.value();
                       auto& variant = drawable.drawable;

                       if (std::holds_alternative<Text>(variant)) {
                         auto& text = std::get<Text>(variant);
                         if (target == MouseEventTarget::kLocalTarget) {
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
  const auto point = Vector3f(managers_.window->GetWidth() / 2, managers_.window->GetHeight() / 2 + 110);
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  registry_->AddComponent<Position>(exit_button, {point, aligns});
  registry_->AddComponent<Drawable>(exit_button,
                                    {Text{"Exit", "main", 20}, WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      exit_button,
      OnMousePressed{.strategy = MouseEventTarget::kLocalTarget,
                     .handler = [this](const sf::Mouse::Button& button, const sf::Vector2f& pos,
                                       MouseEventTarget target) {
                       if (button == sf::Mouse::Button::Left) {
                         managers_.scenes->Quit();
                       }
                     }});
  registry_->AddComponent<OnMouseMoved>(
      exit_button, OnMouseMoved{.strategy = MouseEventTarget::kAnyTarget,
                                .handler = [this, exit_button](const sf::Vector2f& pos,
                                                               const MouseEventTarget& target) {
                                  auto drawables = registry_->GetComponents<Drawable>();

                                  auto& dr = (*drawables)[static_cast<std::size_t>(exit_button)];

                                  if (dr) {
                                    auto& drawable = dr.value();
                                    auto& variant = drawable.drawable;

                                    if (std::holds_alternative<Text>(variant)) {
                                      auto& text = std::get<Text>(variant);
                                      if (target == MouseEventTarget::kLocalTarget) {
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
  constexpr const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  const auto point =
      Vector3f(managers_.window->GetWidth() / 2, managers_.window->GetHeight() - 100);

  registry_->AddComponent<Position>(label, {point, aligns});
  registry_->AddComponent<Tags>(label, Tags({"connection_label"}));
  registry_->AddComponent<Drawable>(label, {Text{.text = GetConnectionLabelText(),
                                                 .fontName = "main",
                                                 .characterSize = 13,
                                                 .color = GetConnectionLabelColor()},
                                            WindowManager::View::HUD});
}
sf::Color SceneMenu::GetConnectionLabelColor() const {
  if (serverConnectionService_->Connected()) {
    return {3, 138, 10, 255};
  } else {
    return {0, 93, 140, 255};
  }
}

std::string SceneMenu::GetConnectionLabelText() const {
  if (serverConnectionService_->Connected()) {
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
