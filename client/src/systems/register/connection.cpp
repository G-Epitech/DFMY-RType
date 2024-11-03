/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** blink.cpp
*/

#include "connection.hpp"

#include "scenes/menu.hpp"

rtype::client::systems::ConnectionSystem::ConnectionSystem(
    services::ServerConnectionService::Ptr serverConnectionService,
    mew::managers::ScenesManager::Ptr scenesManager)
    : serverConnectionService_{std::move(serverConnectionService)},
      scenesManager_{std::move(scenesManager)} {}

void rtype::client::systems::ConnectionSystem::Run(std::shared_ptr<Registry> r) {
  if (serverConnectionService_->Connected()) {
    scenesManager_->GoToScene<scenes::SceneMenu>();
  }
}
