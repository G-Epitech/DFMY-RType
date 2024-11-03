/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** menu.cpp
*/

#include "register.hpp"

#include "constants/settings.hpp"
#include "leaderboard.hpp"
#include "libs/mew/src/sets/drawable/drawable.hpp"
#include "libs/mew/src/sets/events/events.hpp"
#include "systems/blink.hpp"
#include "systems/register/connection.hpp"
#include "systems/utils/input_cursor.hpp"
#include "utils/input.hpp"

using namespace rtype::client::scenes;
using namespace rtype::client::services;
using namespace mew::sets::drawable;
using namespace mew::sets::events;
using namespace mew::managers;
using namespace zygarde::core::components;
using namespace zygarde::core::types;

SceneRegister::SceneRegister(DependenciesHandler::Ptr services) : SceneBase(std::move(services)) {
  registry_->RegisterComponent<Tags>();
  registry_->AddSystem<systems::BlinkSystem>();
  constexpr Alignment alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  registry_->AddSystem<systems::utils::input::CursorSystem>(alignment);
  const Vector3f pos{managers_.window->width_ / 2, managers_.window->height_ / 2 - 50, 0};

  utils::Input::Create(registry_, "connection", pos, alignment, 30);
  serverConnectionService_ = services_->GetOrThrow<ServerConnectionService>();
  settingsManager_ = services_->GetOrThrow<SettingsManager>();
  registry_->AddSystem<systems::ConnectionSystem>(serverConnectionService_, managers_.scenes);
}

void SceneRegister::OnCreate() {
  CreateTitle();
  CreateConnectButton();
  CreateExitButton();
  CreateServerConnectionLabel();
}

void SceneRegister::OnActivate() {}

void SceneRegister::Update(DeltaTime delta_time) {
  UpdateConnectionLabel();
  registry_->RunSystems();
}

void SceneRegister::CreateTitle() const {
  const auto title = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  const auto point = Vector3f(managers_.window->width_ / 2, managers_.window->height_ / 2 - 250);

  registry_->AddComponent<Position>(title, {point, aligns});
  registry_->AddComponent<Drawable>(title,
                                    {Text{"Your Name", "main", 70}, WindowManager::View::HUD});
}

void SceneRegister::CreateConnectButton() const {
  const auto connect_button = registry_->SpawnEntity();
  const auto point = Vector3f(managers_.window->width_ / 2, managers_.window->height_ / 2 + 50);
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(connect_button, {point, aligns});
  registry_->AddComponent<Drawable>(connect_button,
                                    {Text{"Connect", "main", 20}, WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      connect_button,
      OnMousePressed{.strategy = MouseEventTarget::kLocalTarget,
                     .handler = [this](const sf::Mouse::Button& button, const sf::Vector2f& pos,
                                       const MouseEventTarget& target) {
                       if (button == sf::Mouse::Button::Left) {
                         const auto all_tags = registry_->GetComponents<Tags>();
                         const auto all_drawables = registry_->GetComponents<Drawable>();
                         if (!all_tags || !all_drawables)
                           return;
                         for (std::size_t i = 0; i < all_tags->size(); i++) {
                           if (!(*all_tags)[i])
                             continue;
                           if ((*all_tags)[i].value() & "connection_input") {
                             auto& drawable = (*all_drawables)[i];
                             auto& text = std::get<Text>(drawable->drawable);
                             std::cout << "Connecting to server with username: " << text.text
                                       << std::endl;
                             serverConnectionService_->ConnectAsync(text.text);
                             settingsManager_->Set(SETTING_PLAYER_USERNAME, text.text);
                             (*all_tags)[i]->AddTag("disabled");
                           }
                         }
                       }
                     }});
  registry_->AddComponent<OnMouseMoved>(
      connect_button,
      OnMouseMoved{.strategy = MouseEventTarget::kAnyTarget,
                   .handler = [this, connect_button](const sf::Vector2f& pos,
                                                     const MouseEventTarget& target) {
                     auto drawables = registry_->GetComponents<Drawable>();

                     auto& dr = (*drawables)[static_cast<std::size_t>(connect_button)];

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

void SceneRegister::CreateExitButton() const {
  const auto exit_button = registry_->SpawnEntity();
  const auto point = Vector3f(managers_.window->width_ / 2, managers_.window->height_ / 2 + 145);
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

void SceneRegister::CreateServerConnectionLabel() const {
  const auto label = registry_->SpawnEntity();
  constexpr auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  const auto point = Vector3f(managers_.window->width_ / 2, managers_.window->height_ - 100);

  registry_->AddComponent<Position>(label, {point, aligns});
  registry_->AddComponent<Tags>(label, Tags({"connection_label"}));
  registry_->AddComponent<Drawable>(label, {Text{.text = GetConnectionLabelText(),
                                                 .fontName = "main",
                                                 .characterSize = 13,
                                                 .color = GetConnectionLabelColor()},
                                            WindowManager::View::HUD});
}

sf::Color SceneRegister::GetConnectionLabelColor() const {
  switch (serverConnectionService_->connectionStatus()) {
    case ServerConnectionService::ConnectionStatus::kDisconnected:
      return {0, 93, 140, 255};
    case ServerConnectionService::ConnectionStatus::kConnecting:
      return {255, 165, 0, 255};
    case ServerConnectionService::ConnectionStatus::kConnected:
      return {3, 138, 10, 255};
    case ServerConnectionService::ConnectionStatus::kFailed:
      return {255, 0, 0, 255};
    default:
      return {0, 93, 140, 255};
  }
}

std::string SceneRegister::GetConnectionLabelText() const {
  switch (serverConnectionService_->connectionStatus()) {
    case ServerConnectionService::ConnectionStatus::kDisconnected:
      return "Set your username and connect";
    case ServerConnectionService::ConnectionStatus::kConnecting:
      return "Connecting...";
    case ServerConnectionService::ConnectionStatus::kConnected:
      return "Connected";
    case ServerConnectionService::ConnectionStatus::kFailed:
      return "Failed to connect, retrying...";
    default:
      return "Set your username and connect";
  }
}

void SceneRegister::UpdateConnectionLabel() const {
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
