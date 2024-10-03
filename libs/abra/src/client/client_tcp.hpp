/*
** EPITECH PROJECT, 2024
** client_tcp.hpp
** File description:
** ClientTCP class
*/

#pragma once

#include "interface_client.hpp"

namespace abra::client {
class EXPORT_NETWORK_SDK_API ClientTCP;
}

class abra::client::ClientTCP : public abra::client::InterfaceClient {
 public:
  /**
   * @brief Construct a new ClientTCP object
   * @param ip The IP of the server (host)
   * @param port The port of the server
   */
  ClientTCP(const std::string &ip, const std::uint32_t &port);

  ~ClientTCP();

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
  SendMessageStatus send(tools::Packet<T> *packet);

 private:
  boost::asio::io_service ios_;
  boost::asio::ip::tcp::socket socket_;
};

#include "client_tcp.tpp"
