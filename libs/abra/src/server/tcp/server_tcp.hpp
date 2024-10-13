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

#include "./props/message.hpp"
#include "./session/session_tcp.hpp"
#include "libs/abra/src/core.hpp"
#include "libs/abra/src/tools/logger/logger.hpp"

namespace abra::server {
class EXPORT_NETWORK_SDK_API ServerTCP;
}

class abra::server::ServerTCP {
 public:
  /**
   * @brief Construct a new ServerTCP instance
   * @param port The TCP port
   * @param middleware The middleware to catch messages from listeners
   */
  ServerTCP(const int &port, const std::function<bool(const ClientTCPMessage &)> &middleware);

  ~ServerTCP();

  /**
   * @brief Start the server
   */
  void Start();

  /**
   * @brief Send a message to a specific client
   * @tparam T The type of the packet
   * @param packet The packet to send
   * @param clientId The client id
   * @return The status of the message
   */
  template <typename T>
  tools::SendMessageStatus Send(const std::unique_ptr<tools::Packet<T>> &packet,
                                const std::uint64_t &clientId);

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
  [[nodiscard]] const std::shared_ptr<std::queue<ClientTCPMessage>> &GetQueue();

  /**
   * @brief Extract the queue of messages
   * @warning This method will clear the queue
   * @return The queue of messages
   */
  [[nodiscard]] std::queue<ClientTCPMessage> ExtractQueue();

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
  std::shared_ptr<std::queue<ClientTCPMessage>> queue_;

  /// @brief Queue mutex
  std::shared_ptr<std::mutex> mutex_;

  /// @brief Middleware to catch messages from listeners
  std::function<bool(const ClientTCPMessage &)> middleware_;

  /// @brief Logger
  tools::Logger logger_;
};

#include "server_tcp.tpp"
