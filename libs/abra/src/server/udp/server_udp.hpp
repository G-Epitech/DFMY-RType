/*
** EPITECH PROJECT, 2024
** server_udp.hpp
** File description:
** ServerUDP class
*/

#pragma once

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <mutex>
#include <queue>

#include "core.hpp"
#include "props/message.h"
#include "tools/bitset/dynamic_bitset.hpp"
#include "tools/message/message.hpp"
#include "tools/packet/packet.hpp"
#include "tools/packet/props/props.hpp"

namespace abra::server {
class EXPORT_NETWORK_SDK_API ServerUDP;
}

class abra::server::ServerUDP {
 public:
  /**
   * @brief Construct a new ServerUDP object
   * @param port The port of the server
   */
  explicit ServerUDP(const int &port);

  /**
   * @brief Destroy the ServerUDP object
   */
  ~ServerUDP();

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
  [[nodiscard]] std::queue<ClientMessage> &GetQueue();

  /**
   * @brief Send a message to a client
   * @tparam T The type of the packet
   * @param packet The packet to send
   * @param endpoint The endpoint of the client
   * @return The status of the message
   */
  template <typename T>
  tools::SendMessageStatus Send(const std::shared_ptr<tools::Packet<T>> &packet,
                                const boost::asio::ip::udp::endpoint &endpoint);

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
  std::mutex mutex_;
};

#include "server_udp.tpp"