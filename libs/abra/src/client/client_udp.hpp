/*
** EPITECH PROJECT, 2024
** client_udp.hpp
** File description:
** ClientUDP class
*/

#pragma once

#include <memory>

#include "interface_client.hpp"

namespace abra::client {
class EXPORT_NETWORK_SDK_API ClientUDP;
}

class EXPORT_NETWORK_SDK_API abra::client::ClientUDP : public InterfaceClient {
 public:
  /**
   * @brief Construct a new ClientUDP object
   * @param ip The IP of the server (host)
   * @param port The port of the server
   */
  ClientUDP(const std::string &ip, const std::uint32_t &port);

  ~ClientUDP();

  /**
   * @brief Listen the server and handle the incoming data
   */
  void listen() override;

  /**
   * @brief Send a message to the server
   * @param packet The packet to send
   * @return The status of the message
   */
  template <typename T>
  SendMessageStatus send(const std::unique_ptr<tools::Packet<T>> &packet);

 private:
  boost::asio::io_context ioc_;
  boost::asio::ip::udp::endpoint receiverEndpoint_;
  boost::asio::ip::udp::socket socket_;
};

#include "client_udp.tpp"
