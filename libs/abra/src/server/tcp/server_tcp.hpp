/*
** EPITECH PROJECT, 2024
** server_tcp.hpp
** File description:
** ServerTCP class
*/

#pragma once

#include <boost/asio.hpp>
#include <cstdint>
#include <map>
#include <queue>

#include "core.hpp"
#include "props/message.h"
#include "session/session_tcp.hpp"

namespace abra::server {
class EXPORT_NETWORK_SDK_API ServerTCP;
}

class abra::server::ServerTCP {
 public:
  explicit ServerTCP(const int &port);

  ~ServerTCP();

  /**
   * @brief Start the server
   */
  void Start();

  /**
   * @brief Lock the queue mutex
   */
  void LockQueue();

  /**
   * @brief Unlock the queue mutex
   */
  void UnlockQueue();

  /**
   * @brief Get the queue of client messages
   * @warning You need to lock the queue before using it
   * @return The queue
   */
  [[nodiscard]] const std::shared_ptr<std::queue<ClientMessage>> &GetQueue();

 private:
  /**
   * @brief Accept a new connection
   */
  void AcceptNewConnection();

  /**
   * @brief Register a new client
   * @param client
   */
  void RegisterNewClient(std::shared_ptr<SessionTCP> client, const std::uint64_t &clientId);

  /// @brief Input Output Context
  boost::asio::io_context ioc_;
  /// @brief Acceptor of sockets (TCP protocol)
  boost::asio::ip::tcp::acceptor acceptor_;
  /// @brief Clients map
  std::map<std::uint64_t, std::shared_ptr<SessionTCP>> clients_;
  /// @brief Last client id
  std::uint64_t lastClientId_;
  /// @brief Queue of client messages
  std::shared_ptr<std::queue<ClientMessage>> queue_;
  /// @brief Queue mutex
  std::shared_ptr<std::mutex> mutex_;
};
