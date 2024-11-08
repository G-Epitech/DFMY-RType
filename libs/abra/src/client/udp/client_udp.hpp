/*
** EPITECH PROJECT, 2024
** client_udp.hpp
** File description:
** ClientUDP class
*/

#pragma once

#include <memory>

#include "libs/abra/src/client/abstract_client.hpp"

namespace abra::client {
class EXPORT_NETWORK_SDK_API ClientUDP;
}

class abra::client::ClientUDP final : public AbstractClient {
 public:
  struct ClientEndpoint {
    std::string ip;
    unsigned int port;
  };

  /**
   * @brief Construct a new ClientUDP object
   * @param ip The IP of the server (host)
   * @param port The port of the server
   */
  ClientUDP(const std::string &ip, const std::uint32_t &port, const uint32_t &localPort);

  ~ClientUDP() override;

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
   * @brief Get the endpoint of the client
   * @return The endpoint of the client
   */
  [[nodiscard]] ClientEndpoint GetEndpoint() const;

  /**
   * @brief Close the connection
   */
  void Close();

 private:
  /// @brief The Input Output Context
  boost::asio::io_context ioc_;
  /// @brief Endpoint of the server
  boost::asio::ip::udp::endpoint receiverEndpoint_;
  /// @brief The UDP socket
  boost::asio::ip::udp::socket socket_;
};

#include "client_udp.tpp"
