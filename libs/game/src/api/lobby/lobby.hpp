/*
** EPITECH PROJECT, 2024
** lobby.hpp
** File description:
** Lobby class
*/

#pragma once

#include <cstdint>
#include <map>
#include <thread>

#include "libs/abra/includes/network.hpp"
#include "libs/abra/includes/packet.hpp"
#include "libs/game/src/api/props/message.hpp"
#include "libs/game/src/api/props/network.hpp"
#include "libs/game/src/api/props/payload/payload.hpp"
#include "libs/game/src/core.hpp"

namespace rtype::sdk::game::api {
class EXPORT_GAME_SDK_API Lobby;
}

class rtype::sdk::game::api::Lobby {
 public:
  /**
   * @brief Construct a new Lobby API instance
   * @param port The port of the lobby (tcp communication with the master server)
   * @param newPlayerHandler The handler for new players
   */
  Lobby(int port, const std::function<void(std::uint64_t)> &newPlayerHandler);

  /**
   * @brief Delete the Lobby API instance
   */
  ~Lobby();

  /// @brief A lobby client
  struct LobbyClient {
    std::uint64_t id;                         ///< The client id
    boost::asio::ip::udp::endpoint endpoint;  ///< The client endpoint (remote)
  };

  /**
   * @brief Extract queue of messages
   * @warning The queue is cleared after the extraction
   * @return The queue of messages
   */
  [[nodiscard]] std::queue<std::pair<std::uint64_t, abra::server::ClientUDPMessage>> ExtractQueue();

  /**
   * @brief Send state of players to all clients in a lobby
   * @param state The state of the players
   * @return true if the message is sent
   */
  bool SendPlayersState(const std::vector<payload::PlayerState> &state);

  /**
   * @brief Send state of players to all clients in a lobby
   * @param state The state of the players
   * @return true if the message is sent
   */
  bool SendEnemiesState(const std::vector<payload::EnemyState> &state);

  /**
   * @brief Send state of players to all clients in a lobby
   * @param state The state of the players
   * @return true if the message is sent
   */
  bool SendBulletsState(const std::vector<payload::BulletState> &state);

 private:
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
   * @brief Start the UDP connection (run the IO context)
   */
  void ListenUDP();

  /**
   * @brief Handle the incoming TCP messages
   * @return true if the message must be added to the queue (false if the message is handled)
   */
  [[nodiscard]] bool SystemTCPMessagesMiddleware(const abra::server::ClientTCPMessage &message);

  /**
   * @brief Find a user by endpoint
   * @param endpoint The endpoint of the user
   * @return The user id
   */
  [[nodiscard]] std::uint64_t FindUserByEndpoint(const boost::asio::ip::udp::endpoint &endpoint);

  /**
   * @brief Send a payload to the main server (TCP)
   * @tparam T The type of the payload
   * @param type The type of the message
   * @param payload The payload to send
   * @return true if the message is sent
   */
  template <typename T>
  bool SendPayloadTCP(const MessageLobbyType &type, const T &payload);

  /**
   * @brief Send a payload to all clients (UDP)
   * @tparam T The type of the payload
   * @param type The type of the message
   * @param payload The payload to send
   * @return true if the message is sent
   */
  template <typename T>
  bool SendPayloadsUDP(const MessageLobbyType &type, const T &payload);

  /**
   * @brief Handle the master connection
   * @param message The message of the master
   */
  void HandleMasterConnection(const abra::server::ClientTCPMessage &message);

  /**
   * @brief Handle a new user
   * @param message The message of the master
   */
  void HandleNewUser(const abra::server::ClientTCPMessage &message);

  /// @brief The ABRA Server TCP instance
  abra::server::ServerTCP serverTCP_;

  /// @brief The TCP thread
  std::thread threadTCP_;

  /// @brief The master server id (for TCP communication)
  std::uint64_t masterId_;

  /// @brief The ABRA Server UDP instance for game communication
  abra::server::ServerUDP serverUDP_;

  /// @brief The UDP thread
  std::thread threadUDP_;

  /// @brief Packet builder
  abra::tools::PacketBuilder packetBuilder_;

  /// @brief The list of clients connected to the lobby
  std::vector<LobbyClient> clients_;

  /// @brief The logger
  abra::tools::Logger logger_;

  /// @brief This lobby id
  std::uint64_t lobbyId_;

  /// @brief Handler for new player (connection to lobby)
  std::function<void(std::uint64_t)> newPlayerHandler_;

  /// @brief Map of handlers for the TCP messages
  static inline std::map<unsigned int, void (Lobby::*)(const abra::server::ClientTCPMessage &)>
      handlers_ = {
          {MessageServerType::kRegisterLobby, &Lobby::HandleMasterConnection},
          {MessageServerType::kUserJoinLobby, &Lobby::HandleNewUser},
  };
};

#include "libs/game/src/api/lobby/lobby.tpp"
