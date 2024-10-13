/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** sync.hpp
*/

#pragma once

#include "components/server_entity_id.hpp"
#include "core/types/vector/vector_2f.hpp"
#include "libs/zygarde/src/system_abstract.hpp"
#include "managers/server_connection_manager.hpp"

namespace rtype::client::systems {
class GameSyncSystem final : public ASystem<components::ServerEntityId> {
 public:
  /**
   * @brief Construct a new Game Sync System object
   * @param serverConnectionManager Pointer to the server connection manager
   */
  explicit GameSyncSystem(const ServerConnectionManager::Ptr &serverConnectionManager);

  void Run(Registry::Ptr r,
           sparse_array<components::ServerEntityId>::ptr component) override;

 private:
  ServerConnectionManager::Ptr serverConnectionManager_;

  std::vector<Entity> entities_;

  void CreatePlayer(const std::shared_ptr<Registry> &registry, const std::size_t &id, const zygarde::core::types::Vector3f &pos);
};
}  // namespace rtype::client::systems
