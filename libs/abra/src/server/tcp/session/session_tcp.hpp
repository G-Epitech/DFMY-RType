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

#include "core.hpp"
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
  explicit SessionTCP(boost::asio::ip::tcp::socket socket);

  ~SessionTCP();

  /**
   * @brief Start the client session
   */
  void Start();

  template <typename T>
  tools::SendMessageStatus Send(const std::shared_ptr<tools::Packet<T>> &packet);

 private:
  /**
   * @brief Listen the new request of the client
   */
  void ListenNewRequest();

  /**
   * @brief Handle the request of the client
   * @param size The size of the request
   */
  void HandleRequest(const std::size_t &size);

  /// @brief The socket of the client
  boost::asio::ip::tcp::socket socket_;

  /// @brief The buffer of the client
  boost::array<char, kPacketMaxBytesSize> buffer_{};

  /// @brief Message queue
  std::queue<tools::MessageProps> queue_;
};

#include "session_tcp.tpp"
