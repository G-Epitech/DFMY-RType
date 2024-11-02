/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** sync.cpp
*/

#include "sync.hpp"

#include <set>
#include <utility>

using namespace rtype::client::systems;
using namespace rtype::client::components;
using namespace rtype::client::services;
using namespace zygarde::core::types;

LeaderboardSyncSystem::LeaderboardSyncSystem(ServerConnectionService::Ptr server_connection_service,
                                             std::shared_ptr<std::vector<payload::Score>> scores)
    : ASystem(),
      serverConnectionService_{std::move(server_connection_service)},
      scores_(std::move(scores)) {}

void LeaderboardSyncSystem::Run(Registry::Ptr r) {
  if (!serverConnectionService_->Connected()) {
    return;
  }

  auto queue = serverConnectionService_->client()->ExtractQueue();
  while (!queue.empty()) {
    auto &message = queue.front();
    if (message.messageType == MasterToClientMsgType::kMsgTypeMTCInfoGame) {
      auto infos = serverConnectionService_->client()->ResolveGameInfo(message);

      scores_->clear();
      for (auto &score : infos.leaderboard) {
        scores_->push_back(score);
      }
    }

    queue.pop();
  }
}
