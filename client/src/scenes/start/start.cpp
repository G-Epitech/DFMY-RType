/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** start.cpp
*/

#include "start.hpp"

#include <utility>

#include "./entities/text_entity.hpp"
#include "client/src/scenes/menu.hpp"
#include "client/src/ui/button/button.hpp"
#include "client/src/ui/select/select.hpp"
#include "libs/mew/src/managers/window_manager.hpp"
#include "libs/zygarde/src/core/components/position/position.hpp"

using namespace rtype::client::scenes;
using namespace rtype::client::ui;
using namespace zygarde;
using namespace zygarde::core::components;
using namespace zygarde::core::types;
using namespace rtype::client::services;
using namespace porygon;
using namespace mew::managers;

SceneStart::SceneStart(DependenciesHandler::Ptr services) : SceneBase(std::move(services)) {
  serverConnectionService_ = services_->GetOrThrow<ServerConnectionService>();
  Select::RegisterDependencies(registry_);
}

void SceneStart::OnCreate() {
  CreateStaticLabels();
  CreateControls();
  CreateBackButton();
  CreateNodeSelect();
  CreateRoomSelect();
  CreateNodeSelectLabel();
  CreateRoomSelectLabel();
}

void SceneStart::Update(DeltaTime delta_time) {
  /*  auto center = managers_.window->GetCenter();

    counter_ += 1;
    if (counter_ == 500) {
      static const Select::Properties props = {
          .id = "node",
          .position = Vector3f(center.x - 470, center.y - 200),
          .size = Vector2f(370, 25),
          .placeholder = "No node available",
          .options = {{"1", "Node 12"}, {"2", "Node 25"}, {"3", "Node 13"}, {"4", "Node 14"}},
          .selectedOption = Select::GetValue(registry_, "node"),
      };
      Select::Update(registry_, props);
    }*/
  registry_->RunSystems();
}

void SceneStart::CreateStaticLabels() {
  auto center = managers_.window->GetCenter();

  registry_->SpawnEntity<TextEntity>(TextEntity::Properties{
      "Let's start",
      Vector3f(center.x, 165),
      "main",
      40,
      sf::Color::White,
      {HorizontalAlign::kCenter, VerticalAlign::kCenter},
  });
  registry_->SpawnEntity<TextEntity>(TextEntity::Properties{
      "Select a node and a room to start",
      Vector3f(center.x, 215),
      "main",
      13,
      sf::Color::White,
      {HorizontalAlign::kCenter, VerticalAlign::kCenter},
  });
}

void SceneStart::CreateNodeSelect() {
  auto center = managers_.window->GetCenter();
  static const Select::Properties props = {
      .id = "node",
      .position = Vector3f(center.x - 440, center.y - 180),
      .size = Vector2f(370, 25),
      .placeholder = "No node available",
      .options = {{"1", "Node 1"}, {"2", "Node 2"}, {"3", "Node 3"}, {"4", "Node 4"}},
  };

  Select::Create(registry_, props);
}

void SceneStart::CreateNodeSelectLabel() {
  auto center = managers_.window->GetCenter();
  registry_->SpawnEntity<TextEntity>(TextEntity::Properties{
      "Node",
      Vector3f(center.x - 440, center.y - 210),
      "main",
      13,
      sf::Color::White,
      {HorizontalAlign::kLeft, VerticalAlign::kCenter},
  });
}

void SceneStart::CreateRoomSelect() {
  auto center = managers_.window->GetCenter();
  static const Select::Properties props = {
      .id = "room",
      .position = Vector3f(center.x + 70, center.y - 180),
      .size = Vector2f(370, 25),
      .placeholder = "No room available",
      .options = {},
  };

  Select::Create(registry_, props);
}

void SceneStart::CreateRoomSelectLabel() {
  auto center = managers_.window->GetCenter();
  registry_->SpawnEntity<TextEntity>(TextEntity::Properties{
      "Room",
      Vector3f(center.x + 70, center.y - 210),
      "main",
      13,
      sf::Color::White,
      {HorizontalAlign::kLeft, VerticalAlign::kCenter},
  });
}

void SceneStart::CreateControls() {
  auto center = managers_.window->GetCenter();
  Button::Create(registry_, Button::Properties{
                                .id = "new-room",
                                .label = "New room",
                                .fontName = "main",
                                .position = Vector3f(center.x - 90, center.y - 280),
                                .size = Vector2f(100, 20),
                                .disabled = false,
                                .action =
                                    [](const sf::Mouse::Button &button, const sf::Vector2f pos,
                                       const MouseEventTarget &target) {
                                      std::cout << "New room button clicked" << std::endl;
                                    },
                            });
  Button::Create(registry_, Button::Properties{
                                .id = "refresh",
                                .label = "Refresh",
                                .fontName = "main",
                                .position = Vector3f(center.x - 210, center.y - 280),
                                .size = Vector2f(100, 20),
                                .disabled = false,
                                .action =
                                    [](const sf::Mouse::Button &button, const sf::Vector2f pos,
                                       const MouseEventTarget &target) {
                                      std::cout << "Refresh button clicked" << std::endl;
                                    },
                            });
  Button::Create(registry_, Button::Properties{
                                .id = "play",
                                .label = "Join room",
                                .fontName = "main",
                                .position = Vector3f(center.x + 60, center.y - 280),
                                .size = Vector2f(150, 20),
                                .disabled = false,
                                .color = sf::Color::Green,
                                .action =
                                    [](const sf::Mouse::Button &button, const sf::Vector2f pos,
                                       const MouseEventTarget &target) {
                                      std::cout << "Refresh button clicked" << std::endl;
                                    },
                            });
}

void SceneStart::CreateBackButton() {
  const auto exit_button = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  const auto point = Vector3f(managers_.window->GetWidth() / 2, managers_.window->GetHeight() - 50);

  registry_->AddComponent<Position>(exit_button, {point, aligns});
  registry_->AddComponent<Drawable>(exit_button, {Text{"Back", "main", 20}});
  registry_->AddComponent<OnMousePressed>(
      exit_button,
      OnMousePressed{.strategy = MouseEventTarget::kLocalTarget,
                     .handler = [this](const sf::Mouse::Button &button, const sf::Vector2f &pos,
                                       const MouseEventTarget &target) {
                       if (button == sf::Mouse::Button::Left) {
                         managers_.scenes->GoToScene<SceneMenu>();
                       }
                     }});
  registry_->AddComponent<OnMouseMoved>(
      exit_button, OnMouseMoved{.strategy = MouseEventTarget::kAnyTarget,
                                .handler = [this, exit_button](const sf::Vector2f &pos,
                                                               const MouseEventTarget &target) {
                                  auto drawables = registry_->GetComponents<Drawable>();

                                  auto &dr = (*drawables)[static_cast<std::size_t>(exit_button)];

                                  if (dr) {
                                    auto &drawable = dr.value();
                                    auto &variant = drawable.drawable;

                                    if (std::holds_alternative<Text>(variant)) {
                                      auto &text = std::get<Text>(variant);
                                      if (target == MouseEventTarget::kLocalTarget) {
                                        text.style = sf::Text::Style::Underlined;
                                      } else {
                                        text.style = sf::Text::Style::Regular;
                                      }
                                    }
                                  }
                                }});
}
