/*
** EPITECH PROJECT, 2024
** monitor.hpp
** File description:
** Monitor class
*/

#pragma once

#include "libs/abra/includes/network.hpp"
#include "libs/abra/src/tools/logger/logger.hpp"
#include "libs/game/src/api/props/network.hpp"
#include "libs/game/src/api/server/props/client.hpp"
#include "libs/game/src/core.hpp"

namespace rtype::sdk::game::api {
class EXPORT_GAME_SDK_API Monitor;
}

class rtype::sdk::game::api::Monitor {
 public:
  /**
   * @brief Construct a new Monitor websocket object
   */
  Monitor(std::string token, const std::function<void(std::uint64_t)> &onConnect);

  /**
   * @brief Destroy the Monitor object
   */
  ~Monitor();

  /**
   * @brief Handle a message
   * @param message The message
   */
  void MessageHandler(const std::pair<std::uint64_t, const boost::json::object &> &message);

  /**
   * @brief Send players to the monitor
   * @param clientId The client id
   * @param clients The clients
   */
  void SendPlayersToClient(std::uint64_t clientId, const std::vector<ClientProps> &clients);

  /**
   * @brief Send players to the monitor
   */
  void SendPlayersToClients(const std::vector<ClientProps> &clients);

 private:
  /// @brief The websocket server
  abra::server::ServerWebsocket ws_;

  /// @brief Thread of the server
  std::thread websocketThread_;

  /// @brief Master token
  std::string token_;

  /// @brief The logger
  abra::tools::Logger logger_;

  /// @brief The connected clients
  std::vector<std::uint64_t> clients_;

  /// @brief The on connect callback
  std::function<void(std::uint64_t)> onConnect_;

  /**
   * @brief Handle the auth message
   * @param clientId The client id
   * @param message The message
   */
  void AuthHandler(std::uint64_t clientId, const boost::json::object &message);

  /// @brief Messages handlers
  std::map<std::string, void (Monitor::*)(std::uint64_t clientId, const boost::json::object &)>
      handlers_ = {
          {"auth", &Monitor::AuthHandler},
  };
};
