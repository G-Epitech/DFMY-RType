/*
** EPITECH PROJECT, 2024
** client_tcp.hpp
** File description:
** ClientTCP class
*/

#pragma once

#include <memory>

#include "libs/abra/src/client/abstract_client.hpp"

namespace abra::client {
class EXPORT_NETWORK_SDK_API ClientTCP;
}

class abra::client::ClientTCP final : public abra::client::AbstractClient {
 public:
  /**
   * @brief Construct a new ClientTCP object
   * @param ip The IP of the server (host)
   * @param port The port of the server
   */
  ClientTCP(const std::string &ip, const std::uint32_t &port);

  ~ClientTCP() override;

  /**
   * @brief Listen the server and handle the incoming data
   */
  void Listen() override;

  /**
   * @brief Send a message to the server
   * @param packet The packet to Send
   * @return The status of the message
   */
  template <typename T>
  tools::SendMessageStatus Send(const std::unique_ptr<tools::Packet<T>> &packet);

  /**
   * @brief Get the queue of messages
   * @return The queue of messages
   */
  std::queue<tools::MessageProps> &GetQueue();

  /**
   * @brief Close the connection
   */
  void Close();

 private:
  /// @brief The Input Output Service
  boost::asio::io_service ios_;

  /// @brief The TCP socket
  boost::asio::ip::tcp::socket socket_;
};

#include "client_tcp.tpp"
