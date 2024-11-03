/*
** EPITECH PROJECT, 2024
** session_tcp.hpp
** File description:
** SessionTCP class
*/

#pragma once

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/json.hpp>
#include <memory>
#include <queue>

#include "libs/abra/src/core.hpp"
#include "libs/abra/src/server/tcp/props/message.hpp"
#include "libs/abra/src/tools/logger/logger.hpp"
#include "libs/abra/src/tools/message/message.hpp"
#include "libs/abra/src/tools/packet/packet.hpp"
#include "libs/abra/src/tools/packet/props/props.hpp"

namespace abra::server {
class EXPORT_NETWORK_SDK_API SessionWebsocket;
}  // namespace abra::server

class abra::server::SessionWebsocket : public std::enable_shared_from_this<SessionWebsocket> {
 public:
  /**
   * @brief Construct a new SessionTCP. This session will handle incoming data
   * @param socket Client socket
   */
  SessionWebsocket(boost::asio::ip::tcp::socket socket, std::uint64_t clientId,
                   const std::function<void(const boost::json::object &)> &handler_);

  /**
   * @brief Destroy the SessionTCP object
   */
  ~SessionWebsocket();

  /**
   * @brief Start the client session
   */
  void Start();

  /**
   * @brief Close the connection
   */
  void Close();

 private:
  /**
   * @brief Listen the new request of the client
   */
  void ListenNewRequest();

  /**
   * @brief Handle the request of the client
   * @param message The message received
   */
  void HandleRequest(const std::string &message);

  /// @brief The socket of the client
  boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws_;

  /// @brief The buffer of the client
  boost::beast::flat_buffer buffer_;

  /// @brief Client id
  std::uint64_t clientId_;

  /// @brief Handler
  std::function<void(const boost::json::object &)> handler_;

  /// @brief Logger
  tools::Logger logger_;
};
