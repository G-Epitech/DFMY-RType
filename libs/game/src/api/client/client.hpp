/*
** EPITECH PROJECT, 2024
** client.hpp
** File description:
** Client class
*/

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <thread>

#include "abra/includes/network.hpp"
#include "abra/includes/packet.hpp"
#include "api/props/message.hpp"
#include "api/props/payload/payload.hpp"
#include "core.hpp"

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
   * @return true if the client is connected
   */
  [[nodiscard]] bool IsConnected() const;

  /**
   * @brief Connect the client to the server
   * The connection confirmation is handled by the method.
   * This method is blocking for a maximum defined in kServerResponseTimeout.
   * @return true if the packet is sent, false otherwise
   */
  [[nodiscard]] bool connect(const payload::Connection &payload);

 private:
  /// @brief The server response timeout
  static constexpr std::size_t kServerResponseTimeout = 1000 * 5;

  /**
   * @brief Initialize the TCP connection
   */
  void InitTCP();

  /**
   * @brief Start the TCP connection (run the IO service)
   */
  void ListenTCP();

  /**
   * @brief Handle TCP connection confirmation
   */
  void HandleConnectionConfirmation();

  /// @brief The ABRA Client TCP instance (main connection)
  abra::client::ClientTCP clientTCP_;

  /// @brief The ABRA Client UDP instance (specific game connection)
  /// @warning The UDP connection is used for the game only, it's not initialized by default
  std::optional<abra::client::ClientUDP> clientUDP_;

  /// @brief Packet builder
  abra::tools::PacketBuilder packetBuilder_;

  /// @brief The thread to listen the server (TCP)
  std::thread threadTCP_;

  /// @brief The thread to listen the server (UDP)
  std::thread threadUDP_;

  /// @brief Boolean to know if the client is connected to the server
  /// @warning It's a r-type protocol information, it's not related to the TCP connection
  bool isConnected_;
};
