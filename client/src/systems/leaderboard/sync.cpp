/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** sync.cpp
*/

#include "sync.hpp"

#include <set>
#include <utility>

#include "client/src/services/server_connection_service.hpp"
#include "client/src/systems/game/texture_mapper/texture_mapper.hpp"
#include "libs/mew/src/sets/drawable/drawable.hpp"
#include "libs/zygarde/src/core/components/components.hpp"

using namespace rtype::client::systems;
using namespace rtype::client::components;
using namespace rtype::client::services;
using namespace zygarde::core::components;
using namespace zygarde::core::types;
using namespace mew::sets::drawable;

LeaderboardSyncSystem::LeaderboardSyncSystem(ServerConnectionService::Ptr server_connection_service)
    : ASystem(), serverConnectionService_{std::move(server_connection_service)} {}

void LeaderboardSyncSystem::Run(Registry::Ptr r) {
  if (!serverConnectionService_->Connected()) {
    return;
  }

  auto queue = serverConnectionService_->client()->ExtractQueue();
  while (!queue.empty()) {
    auto& message = queue.front();
    // ah
    queue.pop();
  }
}
