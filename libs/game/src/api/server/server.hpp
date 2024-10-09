/*
** EPITECH PROJECT, 2024
** server.hpp
** File description:
** Server class
*/

#pragma once

#include <cstdint>
#include <thread>

#include "abra/includes/network.hpp"
#include "abra/includes/packet.hpp"
#include "api/props/message.hpp"
#include "api/props/network.hpp"
#include "api/props/payload/payload.hpp"
#include "core.hpp"

namespace rtype::sdk::game::api {
class EXPORT_GAME_SDK_API Server;
}

class rtype::sdk::game::api::Server {
 public:
  /**
   * @brief Construct a new Server API instance
   * @param port The port of the server (Main TCP port)
   */
  explicit Server(int port);

 private:
  /**
   * @brief Initialize the TCP connection
   */
  void InitTCP();

  /**
   * @brief Start the TCP connection (run the IO service)
   */
  void ListenTCP();

  /**
   * @brief Handle the incoming TCP messages
   * @return true if the message must be added to the queue (false if the message is handled)
   */
  [[nodiscard]] bool SystemTCPMessagesMiddleware(const ClientTCPMessage &message);

  /// @brief The ABRA Server TCP instance (monitor)
  abra::server::ServerTCP serverTCP_;

  /// @brief The thread that will run the TCP listener
  std::thread threadTCP_;
};
