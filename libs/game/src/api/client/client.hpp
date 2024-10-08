/*
** EPITECH PROJECT, 2024
** client.hpp
** File description:
** Client class
*/

#pragma once

#include <string>
#include <cstdint>

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

private:
  /// @brief The ABRA Client TCP instance (main connection)
  abra::client::ClientTCP clientTCP_;
  /// @brief The ABRA Client UDP instance (specific game connection)
  /// @warning The UDP connection is used for the game only, it's not initialized by default
  abra::client::ClientUDP clientUDP_;
};
