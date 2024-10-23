/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** state_broadcaster.hpp
*/

#pragma once

#include <memory>

#include "libs/game/includes/api.hpp"
#include "registry.hpp"

namespace rtype::server::game {
class StateBroadcaster final {
 public:
  StateBroadcaster() = delete;

  /**
   * Start broadcasting the state of the game to the clients of the lobby
   * @param registry Registry of the game
   * @param api API of the lobby
   */
  static void Run(const std::shared_ptr<zygarde::Registry> &registry,
                  const std::shared_ptr<rtype::sdk::game::api::Lobby> &api);

 private:
  struct EntityStates {
    std::vector<payload::PlayerState> playerStates;
    std::vector<payload::EnemyState> enemyStates;
    std::vector<payload::BulletState> bulletStates;
  };

 private:
  /**
   * Gather the entity states from the registry
   * @brief registry Registry of the game
   * @param states EntityStates object to store the states
   */
  static void GatherEntityStates(const std::shared_ptr<zygarde::Registry> &registry,
                                 const std::unique_ptr<EntityStates> &states) noexcept;

  /**
   * Sends the states to the clients of the lobby
   * @param api API of the lobby
   * @param states EntityStates object containing the states
   */
  static void SendStates(const std::shared_ptr<rtype::sdk::game::api::Lobby> &api,
                         const std::unique_ptr<EntityStates> &states);
};
}  // namespace rtype::server::game
