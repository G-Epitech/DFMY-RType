/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** sync.cpp
*/

#include "sync.hpp"

#include "components/drawable.hpp"
#include "libs/zygarde/src/core/components/position/position.hpp"

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

void GameSyncSystem::CreatePlayer(const std::shared_ptr<Registry>& registry,
                                  const std::size_t& id, const zygarde::core::types::Vector3f& pos) {
  auto player = registry->SpawnEntity();
  static const sf::IntRect base{100, 0, 32, 16};

  registry->AddComponent<components::ServerEntityId>(player, {.id = id});
  registry->AddComponent<zygarde::core::components::Position>(
      player, {.point = pos,
               .aligns = {core::components::HorizontalAlign::kLeft,
                          core::components::VerticalAlign::kTop}});
  registry->AddComponent<components::Drawable>(
      player, {
                  .drawable = components::Texture{.name = "player", .scale = 3, .rect = base},
              });
  entities_[id] = player;
}
