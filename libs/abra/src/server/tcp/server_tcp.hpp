/*
** EPITECH PROJECT, 2024
** server_tcp.hpp
** File description:
** ServerTCP class
*/

#pragma once

#include <boost/asio.hpp>
#include <cstdint>

#include "core.hpp"

namespace abra::server {
class EXPORT_NETWORK_SDK_API ServerTCP;
}

class abra::server::ServerTCP {
 public:
  explicit ServerTCP(const int &port);

  ~ServerTCP();

  /**
   * @brief Start the server
   */
  void Start();

 private:
  /**
   * @brief Accept a new connection
   */
  void AcceptNewConnection();

  /// @brief Input Output Context
  boost::asio::io_context ioc_;
  /// @brief Acceptor of sockets (TCP protocol)
  boost::asio::ip::tcp::acceptor acceptor_;
};
