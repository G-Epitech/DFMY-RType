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

#include "../../core.hpp"
#include "props/message.h"
#include "tools/bitset/dynamic_bitset.hpp"
#include "tools/message/message.hpp"
#include "tools/packet/packet.hpp"
#include "tools/packet/props/props.hpp"
#include "tools/logger/logger.hpp"

namespace abra::server {
class EXPORT_NETWORK_SDK_API ServerUDP;
}

class abra::server::ServerUDP {
 public:
  struct ServerEndpoint {
    std::string ip;
    unsigned int port;
  };

  /**
   * @brief Construct a new ServerUDP object
   * @param port The port of the server
   */
  explicit ServerUDP(const std::uint64_t &port);

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
  [[nodiscard]] std::queue<ClientUDPMessage> &GetQueue();

  /**
   * @brief Send a message to a client
   * @tparam T The type of the packet
   * @param packet The packet to send
   * @param endpoint The endpoint of the client
   * @return The status of the message
   */
  template <typename T>
  tools::SendMessageStatus Send(const std::unique_ptr<tools::Packet<T>> &packet,
                                const boost::asio::ip::udp::endpoint &endpoint);

  /**
   * @brief Get the endpoint of the client
   * @return The endpoint of the client
   */
  [[nodiscard]] ServerEndpoint GetEndpoint() const;

  /**
   * @brief Extract the queue of messages
   * @warning This method will clear the queue
   * @return The queue of messages
   */
  [[nodiscard]] std::queue<ClientUDPMessage> ExtractQueue();

  /**
   * @brief Close the server
   */
  void Close();

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

  /**
   * @brief Resolve the buffer (use if we receive multiple packets in one buffer)
   * @param buffer The buffer to resolve
   * @param len The length of the buffer
   */
  void ResolveBuffer(std::vector<char> *buffer, std::size_t len);

  /**
   * @brief Store a message in the queue
   * @param bitset The bitset of the message
   */
  void StoreMessage(std::shared_ptr<tools::dynamic_bitset> bitset);

  /// @brief The Input/Output service
  boost::asio::io_service ios_;

  /// @brief The socket of the server
  boost::asio::ip::udp::socket socket_;

  /// @brief The endpoint of the client (use for the receive)
  boost::asio::ip::udp::endpoint remoteEndpoint_;

  /// @brief The buffer of the server (use for the receive)
  boost::array<char, kPacketMaxBytesSize> buffer_;

  /// @brief The queue of client messages
  std::queue<ClientUDPMessage> queue_;

  /// @brief The mutex of the queue
  std::mutex mutex_;

  /// @brief The logger of the server
  tools::Logger logger_;
};

#include "server_udp.tpp"
