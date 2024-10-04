/*
** EPITECH PROJECT, 2024
** session_tcp.hpp
** File description:
** SessionTCP class
*/

#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <queue>

#include "core.hpp"
#include "tools/message/message.hpp"

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

 private:
  /**
   * @brief Listen the new request of the client
   */
  void ListenNewRequest();

  /// @brief The socket of the client
  boost::asio::ip::tcp::socket socket_;

  /// @brief The buffer of the client
  std::vector<char> buffer_;

  /// @brief Message queue
  std::queue<tools::MessageProps> queue_;
};
