/*
** EPITECH PROJECT, 2024
** server_tcp.hpp
** File description:
** ServerTCP class
*/

#pragma once

#include <boost/asio.hpp>
#include <cstdint>
#include <map>

#include "core.hpp"
#include "session/session_tcp.hpp"

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

  /**
   * @brief Register a new client
   * @param client
   */
  void RegisterNewClient(std::shared_ptr<SessionTCP> client);

  /// @brief Input Output Context
  boost::asio::io_context ioc_;
  /// @brief Acceptor of sockets (TCP protocol)
  boost::asio::ip::tcp::acceptor acceptor_;
  /// @brief Clients map
  std::map<std::uint64_t, std::shared_ptr<SessionTCP>> clients_;
  /// @brief Last client id
  std::uint64_t lastClientId_;
};
