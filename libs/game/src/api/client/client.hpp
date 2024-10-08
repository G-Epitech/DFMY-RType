/*
** EPITECH PROJECT, 2024
** client.hpp
** File description:
** Client class
*/

#pragma once

#include <string>
#include <cstdint>
#include <optional>
#include <thread>

#include "core.hpp"
#include "abra/includes/network.hpp"

namespace rtype::sdk::game::api {
  class EXPORT_GAME_SDK_API Client;
}

class rtype::sdk::game::api::Client {
public:
  /**
   * @brief Construct a new Client API instance
   * @param ip The IP of the server
   * @param port The port of the server (Main TCP port)
   * @warning Do not use localhost or domain for the IP
   */
  Client(const std::string &ip, const std::uint32_t &port);

  /**
   * @brief Delete the Client API instance
   */
  ~Client();

  /**
   * @brief Check if the client is connected to the server
   */
  [[nodiscard]] bool IsConnected() const;

private:
  /**
   * @brief Initialize the TCP connection
   */
  void InitTCP();

  /**
   * @brief Start the TCP connection (run the IO service)
   */
  void ListenTCP();

  /// @brief The ABRA Client TCP instance (main connection)
  abra::client::ClientTCP clientTCP_;
  /// @brief The ABRA Client UDP instance (specific game connection)
  /// @warning The UDP connection is used for the game only, it's not initialized by default
  std::optional<abra::client::ClientUDP> clientUDP_;
  /// @brief The thread to listen the server (TCP)
  std::thread threadTCP_;
  /// @brief The thread to listen the server (UDP)
  std::thread threadUDP_;
  /// @brief Boolean to know if the client is connected to the server
  /// @warning It's a r-type protocol information, it's not related to the TCP connection
  bool isConnected_;
};
