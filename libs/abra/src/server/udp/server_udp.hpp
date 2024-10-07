/*
** EPITECH PROJECT, 2024
** server_udp.hpp
** File description:
** ServerUDP class
*/

#pragma once

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <queue>

#include "core.hpp"
#include "tools/packet/props/props.hpp"
#include "tools/bitset/dynamic_bitset.hpp"

namespace abra::server {
  class EXPORT_NETWORK_SDK_API ServerUDP;
}

class abra::server::ServerUDP {
public:
  explicit ServerUDP(const int &port);

  ~ServerUDP();

  struct ClientMessage {
    boost::asio::ip::udp::endpoint endpoint;
    unsigned int messageType;
    unsigned int messageId;
    std::shared_ptr<tools::dynamic_bitset> bitset;
  };

  /**
   * @brief Start the server
   */
  void Start();

private:
  /**
   * @brief Listen a new request from a client
   */
  void ListenNewRequest();

  /**
   * @brief Handle the request of the client
   * @param size The size of the request
   */
  void HandleRequest(const std::size_t &size);

  boost::asio::io_service ios_;
  boost::asio::ip::udp::socket socket_;
  boost::asio::ip::udp::endpoint remoteEndpoint_;
  boost::array<char, kPacketMaxBytesSize> buffer_;
  std::queue<ClientMessage> queue_;
};
