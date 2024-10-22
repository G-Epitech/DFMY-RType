/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** start.cpp
*/

#include "start.hpp"

#include <utility>

#include "./entities/title_entity.hpp"
#include "libs/zygarde/src/core/components/position/position.hpp"

using namespace rtype::client::scenes;
using namespace zygarde;
using namespace zygarde::core::components;
using namespace zygarde::core::types;
using namespace rtype::client::services;
using namespace porygon;

SceneStart::SceneStart(DependenciesHandler::Ptr services) : SceneBase(std::move(services)) {
  serverConnectionService_ = services_->GetOrThrow<ServerConnectionService>();
}

void SceneStart::OnCreate() {
  CreateStaticLabels();
}

void SceneStart::CreateStaticLabels() {
  auto center = managers_.window->GetCenter();

  registry_->SpawnEntity<TitleEntity>("Select a room", Vector3f(center.x, center.y - 300));
}
