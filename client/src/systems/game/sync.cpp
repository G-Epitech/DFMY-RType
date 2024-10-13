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

void GameSyncSystem::CreatePlayer(const std::shared_ptr<Registry>& registry, const std::size_t& id,
                                  const zygarde::core::types::Vector3f& pos) {
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

void GameSyncSystem::UpdatePlayer(const std::shared_ptr<Registry>& registry, const std::size_t& id,
                                  const zygarde::core::types::Vector3f& pos) {
  auto player = entities_[id];
  auto positions = registry->GetComponents<zygarde::core::components::Position>();

  if (id >= positions->size()) {
    std::cerr << "Invalid player id" << std::endl;
    return;
  }
  if ((*positions)[id]) {
    (*positions)[id]->point = pos;
  }
}

void GameSyncSystem::DeleteEntity(const std::shared_ptr<Registry>& registry,
                                  const std::size_t& id) {
  const auto entity = entities_[id];

  registry->KillEntity(entity);
  entities_.erase(entities_.begin() + id);
}

void GameSyncSystem::CreateMissile(const std::shared_ptr<Registry>& registry, const std::size_t& id,
                                   const zygarde::core::types::Vector3f& pos) {
  const auto missile = registry->SpawnEntity();
  static const sf::IntRect base{337, 255, 12, 4};

  registry->AddComponent<components::ServerEntityId>(missile, {.id = id});
  registry->AddComponent<zygarde::core::components::Position>(
      missile, {.point = pos,
                .aligns = {core::components::HorizontalAlign::kLeft,
                           core::components::VerticalAlign::kTop}});
  registry->AddComponent<components::Drawable>(
      missile, {
                   .drawable = components::Texture{.name = "missile", .scale = 3, .rect = base},
               });
  entities_[id] = missile;
}

void GameSyncSystem::UpdateMissile(const std::shared_ptr<Registry>& registry, const std::size_t& id,
                                   const zygarde::core::types::Vector3f& pos) {
  auto missile = entities_[id];
  auto positions = registry->GetComponents<zygarde::core::components::Position>();

  if (id >= positions->size()) {
    std::cerr << "Invalid missile id" << std::endl;
    return;
  }
  if ((*positions)[id]) {
    (*positions)[id]->point = pos;
  }
}
