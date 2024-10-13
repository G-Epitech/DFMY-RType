/*
** EPITECH PROJECT, 2024
** server.hpp
** File description:
** Server class
*/

#pragma once

#include <cstdint>
#include <map>
#include <thread>

#include "abra/includes/network.hpp"
#include "abra/includes/packet.hpp"
#include "api/props/message.hpp"
#include "api/props/network.hpp"
#include "api/props/payload/payload.hpp"
#include "core.hpp"

namespace rtype::sdk::game::api {
class EXPORT_GAME_SDK_API Server;
}

class rtype::sdk::game::api::Server {
 public:
  /**
   * @brief Construct a new Server API instance
   * @param port The port of the server (Main TCP port)
   */
  explicit Server(int port);

  /**
   * @brief Delete the Server API instance
   */
  ~Server();

  struct Client {
    std::uint64_t id;
    std::string pseudo;
    bool inLobby;
    std::uint32_t lobbyId;
    boost::asio::ip::udp::endpoint endpoint;
  };

  struct LobbyClient {
    std::uint64_t id;
    boost::asio::ip::udp::endpoint endpoint;
  };

  struct Lobby {
    std::uint64_t id;
    std::string name;
    std::unique_ptr<abra::server::ServerUDP> serverUDP;
    std::vector<LobbyClient> clients;
    std::thread thread;
  };

  /**
   * @brief Create a lobby that will generate a new UDP server
   * @param name Name of the lobby
   * @param newPlayerHandler Handler for new player
   * @warning The handler will be async, please use a mutex when you access to your own resources
   */
  std::uint64_t CreateLobby(const std::string &name,
                            const std::function<void(std::uint64_t)> &newPlayerHandler);

  /**
   * @brief Extract queue of messages
   * It's a mix of TCP and UDP messages
   * @warning The queue is cleared after the extraction
   * @return The queue of messages
   */
  [[nodiscard]] std::queue<ClientTCPMessage> ExtractMainQueue();

  /**
   * @brief Extract queue of messages of a lobby
   * It's a mix of TCP and UDP messages
   * @warning The queue is cleared after the extraction
   * @param id The lobby id
   * @return The queue of messages
   */
  [[nodiscard]] std::queue<std::pair<std::uint64_t, ClientUDPMessage>> ExtractLobbyQueue(
      std::uint64_t id);

  /**
   * @brief Send state of players to all clients in a lobby
   * @param lobbyId The lobby id
   * @param state The state of the players
   * @return true if the message is sent
   */
  bool SendPlayersState(const std::uint64_t &lobbyId,
                        const std::vector<payload::PlayerState> &state);

  /**
   * @brief Send state of players to all clients in a lobby
   * @param lobbyId The lobby id
   * @param state The state of the players
   * @return true if the message is sent
   */
  bool SendEnemiesState(const std::uint64_t &lobbyId,
                        const std::vector<payload::EnemyState> &state);

  /**
   * @brief Send state of players to all clients in a lobby
   * @param lobbyId The lobby id
   * @param state The state of the players
   * @return true if the message is sent
   */
  bool SendBulletsState(const std::uint64_t &lobbyId,
                        const std::vector<payload::BulletState> &state);

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
   * @param id The lobby id
   */
  void InitUDP(std::uint64_t id);

  /**
   * @brief Start the UDP connection (run the IO context)
   * @param id The lobby id
   */
  void ListenUDP(std::uint64_t id);

  /**
   * @brief Send a payload to a specific client (TCP)
   * @tparam T The type of the payload
   * @param type The type of the message
   * @param payload The payload to send
   * @param clientId The client id
   * @return true if the message is sent
   */
  template <typename T>
  bool SendPayloadTCP(const MessageServerType &type, const T &payload,
                      const std::uint64_t &clientId);

  template <typename T>
  bool SendPayloadsToLobby(const MessageServerType &type, const std::vector<T> &payload,
                           const std::uint64_t &lobbyId);

  /**
   * @brief Handle the incoming TCP messages
   * @return true if the message must be added to the queue (false if the message is handled)
   */
  [[nodiscard]] bool SystemTCPMessagesMiddleware(const ClientTCPMessage &message);

  /**
   * @brief Handle a client connection
   * @param message The message of the client
   */
  void HandleClientConnection(const ClientTCPMessage &message);

  /**
   * @brief Handle a lobby join
   * @param message The message of the client
   */
  void HandleLobbyJoin(const ClientTCPMessage &message);

  /**
   * @brief Handle player when he joins a lobby
   * @param message The message of the client
   */
  void HandleLobbyAddPlayer(const ClientTCPMessage &message);

  /**
   * @brief Add a new client to the server
   * @param clientId The client id
   * @param pseudo The pseudo of the client
   */
  void AddNewClient(std::uint64_t clientId, const std::string &pseudo);

  /**
   * @brief Find a user by its endpoint
   * @param lobbyId The lobby id
   * @param endpoint The endpoint of the user
   * @return The user id
   */
  [[nodiscard]] std::uint64_t FindUserByEndpoint(std::uint64_t lobbyId,
                                                 const boost::asio::ip::udp::endpoint &endpoint);

  /// @brief The ABRA Server TCP instance (monitor)
  abra::server::ServerTCP serverTCP_;

  /// @brief The thread that will run the TCP listener
  std::thread threadTCP_;

  /// @brief Packet builder
  abra::tools::PacketBuilder packetBuilder_;

  /// @brief The logger
  abra::tools::Logger logger_;

  /// @brief Vector of clients
  std::vector<Client> clients_;

  /// @brief Map of lobbies
  std::map<std::uint64_t, Lobby> lobbies_;

  /// @brief Handler for new player (connection to lobby)
  std::function<void(std::uint64_t)> newPlayerHandler_;

  /// @brief Map of handlers for the TCP messages
  static inline std::map<unsigned int, void (Server::*)(const ClientTCPMessage &)> handlers_ = {
      {MessageClientType::kConnection, &Server::HandleClientConnection},
      {MessageClientType::kJoinLobby, &Server::HandleLobbyJoin},
      {MessageClientType::kClientJoinLobbyInfos, &Server::HandleLobbyAddPlayer},
  };
};

#include "server.tpp"
