/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** start.cpp
*/

#include "start.hpp"

#include <utility>

#include "./entities/title_entity.hpp"
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
  Select::RegisterDependencies(*registry_);
}

void SceneStart::OnCreate() {
  CreateStaticLabels();
}

void SceneStart::CreateStaticLabels() {
  auto center = managers_.window->GetCenter();
  static const Select::Properties props = {
      .id = "room",
      .position = Vector3f(center.x - 250, center.y - 200),
      .size = Vector2f(500, 30),
      .placeholder = "No rooms available",
      .options = {{"1", "Room 1"}, {"2", "Room 2"}, {"3", "Room 3"}},
  };

  registry_->SpawnEntity<TitleEntity>("Select a room", Vector3f(center.x, center.y - 300));
  Select::Create(registry_, props);
}
