/*
** EPITECH PROJECT, 2024
** session_tcp.hpp
** File description:
** SessionTCP class
*/

#pragma once

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <memory>
#include <queue>

#include "../../../core.hpp"
#include "server/tcp/props/message.h"
#include "tools/message/message.hpp"
#include "tools/packet/packet.hpp"
#include "tools/packet/props/props.hpp"

namespace abra::server {
class EXPORT_NETWORK_SDK_API SessionTCP;
}  // namespace abra::server

class abra::server::SessionTCP : public std::enable_shared_from_this<SessionTCP> {
 public:
  /**
   * @brief Construct a new SessionTCP. This session will handle incoming data
   * @param socket Client socket
   */
  SessionTCP(boost::asio::ip::tcp::socket socket,
             std::shared_ptr<std::queue<ClientTCPMessage>> queue, std::shared_ptr<std::mutex> mutex,
             std::uint64_t clientId,
             const std::function<bool(const ClientTCPMessage&)>& middleware);

  /**
   * @brief Destroy the SessionTCP object
   */
  ~SessionTCP();

  /**
   * @brief Start the client session
   */
  void Start();

  /**
   * @brief Send a message to a client
   * @tparam T The type of the packet
   * @param packet The packet to send
   * @return The status of the message
   */
  template <typename T>
  tools::SendMessageStatus Send(const std::shared_ptr<tools::Packet<T>>& packet);

 private:
  /**
   * @brief Listen the new request of the client
   */
  void ListenNewRequest();

  /**
   * @brief Handle the request of the client
   * @param size The size of the request
   */
  void HandleRequest(const std::size_t& size);

  /// @brief The socket of the client
  boost::asio::ip::tcp::socket socket_;
  /// @brief The buffer of the client
  boost::array<char, kPacketMaxBytesSize> buffer_{};
  /// @brief Message queue
  std::shared_ptr<std::queue<ClientTCPMessage>> queue_;
  /// @brief Client id
  std::uint64_t clientId_;
  /// @brief Queue mutex
  std::shared_ptr<std::mutex> mutex_;
  /// @brief Middleware
  const std::function<bool(const ClientTCPMessage&)>& middleware_;
};

#include "session_tcp.tpp"
