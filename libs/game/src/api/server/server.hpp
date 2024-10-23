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

#include "libs/abra/includes/network.hpp"
#include "libs/abra/includes/packet.hpp"
#include "libs/game/src/api/props/message.hpp"
#include "libs/game/src/api/props/network.hpp"
#include "libs/game/src/api/props/payload/payload.hpp"
#include "libs/game/src/core.hpp"

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

  struct Lobby {
    std::uint64_t id;
    std::string name;
    std::unique_ptr<abra::client::ClientTCP> clientTCP;
    std::thread thread;
    bool enabled;
    char ip[16];
    std::uint64_t port;
  };

  /**
   * @brief Create a lobby that will generate a new UDP server
   * @param name Name of the lobby
   * @param port TCP port of the lobby
   * @warning The handler will be async, please use a mutex when you access to your own resources
   */
  std::uint64_t CreateLobby(const std::string &name, uint64_t port);

  /**
   * @brief Extract queue of messages
   * @warning The queue is cleared after the extraction
   * @return The queue of messages
   */
  [[nodiscard]] std::queue<abra::server::ClientTCPMessage> ExtractMainQueue();

  /**
   * @biref Wait the end of threads
   */
  void Join();

 private:
  /**
   * @brief Initialize the TCP connection
   */
  void InitServerTCP();

  /**
   * @brief Start the TCP connection (run the IO service)
   */
  void ListenServerTCP();

  /**
   * @brief Initialize the TCP connection (for a lobby)
   * @param id The id of the lobby
   */
  void InitClientTCP(std::uint64_t id);

  /**
   * @brief Start the TCP connection (run the IO service) (for a lobby)
   */
  void ListenClientTCP(std::uint64_t id);

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

  /**
   * @brief Send a payload to a specific lobby (TCP)
   * @tparam T The type of the payload
   * @param type The type of the message
   * @param payload The payload to send
   * @param lobbyId The lobby id
   * @return true if the message is sent
   */
  template <typename T>
  bool SendPayloadLobbyTCP(const MessageServerType &type, const T &payload,
                           const std::uint64_t &lobbyId);

  /**
   * @brief Handle the incoming TCP messages
   * @return true if the message must be added to the queue (false if the message is handled)
   */
  [[nodiscard]] bool SystemServerTCPMessagesMiddleware(
      const abra::server::ClientTCPMessage &message);

  /**
   * @brief Handle the incoming TCP messages
   * @return true if the message must be added to the queue (false if the message is handled)
   */
  [[nodiscard]] bool SystemClientTCPMessagesMiddleware(const abra::tools::MessageProps &message,
                                                       std::uint64_t lobbyId);

  /**
   * @brief Handle a client connection
   * @param message The message of the client
   */
  void HandleClientConnection(const abra::server::ClientTCPMessage &message);

  /**
   * @brief Handle a lobby join
   * @param message The message of the client
   */
  void HandleLobbyJoin(const abra::server::ClientTCPMessage &message);

  /**
   * @brief Handle player when he joins a lobby
   * @param message The message of the client
   */
  void HandleLobbyAddPlayer(const abra::server::ClientTCPMessage &message);

  /**
   * @brief Handle the lobby infos
   * @param message The message of the lobby
   */
  void HandleLobbyInfos(const abra::tools::MessageProps &message, std::uint64_t lobbyId);

  /**
   * @brief Add a new client to the server
   * @param clientId The client id
   * @param pseudo The pseudo of the client
   */
  void AddNewClient(std::uint64_t clientId, const std::string &pseudo);

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

  /// @brief Map of handlers for the TCP messages
  static inline std::map<unsigned int, void (Server::*)(const abra::server::ClientTCPMessage &)>
      serverHandlers_ = {
          {MessageClientType::kConnection, &Server::HandleClientConnection},
          {MessageClientType::kJoinLobby, &Server::HandleLobbyJoin},
          {MessageClientType::kClientJoinLobbyInfos, &Server::HandleLobbyAddPlayer},
  };

  /// @brief Map of handlers for the TCP messages
  static inline std::map<unsigned int,
                         void (Server::*)(const abra::tools::MessageProps &, std::uint64_t lobbyId)>
      clientHandlers_ = {
          {MessageLobbyType::kLobbyInfos, &Server::HandleLobbyInfos},
  };
};

#include "server.tpp"
