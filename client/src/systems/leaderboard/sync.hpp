/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** sync.hpp
*/

#pragma once

#include <map>
#include <set>

#include "client/src/services/server_connection_service.hpp"
#include "components/server_entity_id.hpp"
#include "core/types/vector/vector_2f.hpp"
#include "libs/zygarde/src/system_abstract.hpp"

namespace rtype::client::systems {
class LeaderboardSyncSystem final : public ASystem<> {
 public:
  /**
   * @brief Construct a new Leaderboard Sync System object
   * @param server_connection_service Pointer to the server connection service
   */
  explicit LeaderboardSyncSystem(services::ServerConnectionService::Ptr server_connection_service);

  void Run(Registry::Ptr r) override;

 private:
  /**
   * @brief Pointer to the server connection manager
   */
  services::ServerConnectionService::Ptr serverConnectionService_;
};
}  // namespace rtype::client::systems
