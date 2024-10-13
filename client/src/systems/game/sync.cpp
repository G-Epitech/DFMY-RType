/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** sync.cpp
*/

#include "sync.hpp"

using namespace rtype::client::systems;

GameSyncSystem::GameSyncSystem(const ServerConnectionManager::Ptr& serverConnectionManager)
    : serverConnectionManager_{serverConnectionManager} {}

void GameSyncSystem::Run(std::shared_ptr<Registry> r,
                         sparse_array<components::ServerEntityId>::ptr IDs) {
  auto queue = serverConnectionManager_->client()->ExtractQueue();
  while (!queue.empty()) {
    auto& message = queue.front();
    std::cout << "Received message: " << message.messageType << std::endl;

    queue.pop();
  }
}
