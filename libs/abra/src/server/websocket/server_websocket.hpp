/*
** EPITECH PROJECT, 2024
** server_tcp.hpp
** File description:
** ServerTCP class
*/

#pragma once

#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <cstdint>
#include <map>
#include <queue>

#include "./session/session_websocket.hpp"
#include "libs/abra/src/core.hpp"
#include "libs/abra/src/tools/logger/logger.hpp"

namespace abra::server {
class EXPORT_NETWORK_SDK_API ServerWebsocket;
}

class abra::server::ServerWebsocket {
 public:
  /**
   * @brief Construct a new ServerTCP instance
   * @param port The TCP port
   * @param middleware The middleware to catch messages from listeners
   */
  ServerWebsocket(const int &port, const std::function<void(const boost::json::object &)> &handler);

  ~ServerWebsocket();

  /**
   * @brief Start the server
   */
  void Start();

  /**
   * @brief Close the server
   */
  void Close();

 private:
  /**
   * @brief Accept a new connection
   */
  void AcceptNewConnection();

  /**
   * @brief Register a new client
   * @param client
   */
  void RegisterNewClient(std::shared_ptr<SessionWebsocket> client, const std::uint64_t &clientId);

  /// @brief Input Output Context
  boost::asio::io_context ioc_;

  /// @brief Acceptor of sockets (TCP protocol)
  boost::asio::ip::tcp::acceptor acceptor_;

  /// @brief Clients map
  std::map<std::uint64_t, std::shared_ptr<SessionWebsocket>> clients_;

  /// @brief Last client id
  std::uint64_t lastClientId_;

  /// @brief Handler of websocket messages
  std::function<void(const boost::json::object &)> handler_;

  /// @brief Logger
  tools::Logger logger_;
};
