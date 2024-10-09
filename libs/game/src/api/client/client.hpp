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
#include "api/props/network.hpp"
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
  [[nodiscard]] bool Connect(const payload::Connection &payload);

  /**
   * @brief Join a game lobby
   * It will initialize the UDP connection to the game server
   * @param payload The payload to join the lobby
   */
  [[nodiscard]] bool JoinLobby(const payload::JoinLobby &payload);

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
   * @brief Initialize the UDP connection
   */
  void InitUDP();

  /**
   * @brief Start the UDP connection (run the IO contexte)
   */
  void ListenUDP();

  /**
   * @brief Send a payload to the server
   * @tparam T The payload type
   * @param type The message type
   * @param payload The payload to send
   * @return true if the packet is sent, false otherwise
   */
  template <typename T>
  bool SendPayload(const MessageClientType &type, const T &payload);

  /**
   * @brief Wait for a message from the server
   * @tparam T The network protocol type
   * @param type The message type to wait for
   * @param handler The handler to call when the message is received
   * @return true if the message is received and handled, false otherwise
   */
  template <NetworkProtocolType T>
  bool WaitForMessage(MessageServerType type,
                      bool (Client::*handler)(const tools::MessageProps &message));

  /**
   * @brief Handle TCP connection confirmation
   */
  bool HandleConnectionConfirmation(const tools::MessageProps &);

  /**
   * @brief Handle Join lobby and init UDP connection
   * @param message The message with the lobby infos
   */
  bool HandleJoinLobbyInfos(const tools::MessageProps &message);

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

  /// @brief Boolean to know if the client is connected to the lobby
  bool isLobbyConnected_;
};

#include "client.tpp"
