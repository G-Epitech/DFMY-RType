/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** start.cpp
*/

#include "start.hpp"

#include <utility>

#include "./entities/text_entity.hpp"
#include "client/src/ui/select/select.hpp"
#include "libs/zygarde/src/core/components/position/position.hpp"

using namespace rtype::client::scenes;
using namespace rtype::client::ui;
using namespace zygarde;
using namespace zygarde::core::components;
using namespace zygarde::core::types;
using namespace rtype::client::services;
using namespace porygon;

SceneStart::SceneStart(DependenciesHandler::Ptr services) : SceneBase(std::move(services)) {
  serverConnectionService_ = services_->GetOrThrow<ServerConnectionService>();
  Select::RegisterDependencies(registry_);
}

void SceneStart::OnCreate() {
  CreateStaticLabels();
  CreateNodeSelect();
  CreateRoomSelect();
  CreateNodeSelectLabel();
  CreateRoomSelectLabel();
}

void SceneStart::Update(DeltaTime delta_time) {
  auto center = managers_.window->GetCenter();

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
  }
  registry_->RunSystems();
}

void SceneStart::CreateStaticLabels() {
  auto center = managers_.window->GetCenter();

  registry_->SpawnEntity<TextEntity>(TextEntity::Properties{
      "Let's start",
      Vector3f(center.x, 180),
      "main",
      40,
      sf::Color::White,
      {HorizontalAlign::kCenter, VerticalAlign::kCenter},
  });
  registry_->SpawnEntity<TextEntity>(TextEntity::Properties{
      "Select a node and a room to start",
      Vector3f(center.x, 230),
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
      .position = Vector3f(center.x - 470, center.y - 200),
      .size = Vector2f(370, 25),
      .placeholder = "No node available",
      .options = {{"1", "Node 1"}, {"2", "Node 2"}, {"3", "Node 3"}, {"4", "Node 4"}},
  };

  Select::Create(registry_, props);
}

void SceneStart::CreateRoomSelect() {
  auto center = managers_.window->GetCenter();
  static const Select::Properties props = {
      .id = "room",
      .position = Vector3f(center.x + 100, center.y - 200),
      .size = Vector2f(370, 25),
      .placeholder = "No room available",
      .options = {},
  };

  Select::Create(registry_, props);
}

void SceneStart::CreateNodeSelectLabel() {
  auto center = managers_.window->GetCenter();
  registry_->SpawnEntity<TextEntity>(TextEntity::Properties{
      "Node",
      Vector3f(center.x - 470, center.y - 230),
      "main",
      13,
      sf::Color::White,
      {HorizontalAlign::kLeft, VerticalAlign::kCenter},
  });
}

void SceneStart::CreateRoomSelectLabel() {
  auto center = managers_.window->GetCenter();
  registry_->SpawnEntity<TextEntity>(TextEntity::Properties{
      "Room",
      Vector3f(center.x + 100, center.y - 230),
      "main",
      13,
      sf::Color::White,
      {HorizontalAlign::kLeft, VerticalAlign::kCenter},
  });
}
