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

#include "libs/abra/includes/network.hpp"
#include "libs/abra/includes/packet.hpp"
#include "libs/game/src/api/props/message.hpp"
#include "libs/game/src/api/props/network.hpp"
#include "libs/game/src/api/props/payload/payload.hpp"
#include "libs/game/src/core.hpp"

namespace rtype::sdk::game::api {
class EXPORT_GAME_SDK_API Client;
}

class rtype::sdk::game::api::Client {
 public:
  /// @brief Pointer type
  using Ptr = std::shared_ptr<Client>;

  /**
   * @brief Represent a message from the server
   */
  struct ServerMessage {
    unsigned int messageId;            ///< ID of the message
    unsigned int messageType;          ///< Type of the message
    NetworkProtocolType protocolType;  ///< Protocol type of the message
    std::vector<std::shared_ptr<abra::tools::dynamic_bitset>> data;  ///< Content of the message
  };

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
   * @brief Register the client to the server
   * The connection confirmation is handled by the method.
   * This method is blocking for a maximum defined in kServerResponseTimeout.
   * @return true if the packet is sent, false otherwise
   */
  [[nodiscard]] bool Register(const payload::PlayerConnect &payload);

  /**
   * @brief Join a game lobby
   * It will initialize the UDP connection to the game server
   * @param payload The payload to join the lobby
   */
  [[nodiscard]] bool JoinRoom(const payload::JoinRoom &payload);

  /**
   * @brief Create a room
   * @param payload The payload to create the room
   * @return true if the packet is sent, false otherwise
   */
  [[nodiscard]] bool CreateRoom(const payload::CreateRoom &payload);

  /**
   * @brief Extract queue of messages
   * It's a mix of TCP and UDP messages
   * @warning The queue is cleared after the extraction
   * @return The queue of messages
   */
  [[nodiscard]] std::queue<ServerMessage> ExtractQueue();

  /**
   * @brief Extract chat queue of messages
   * @warning The queue is cleared after the extraction
   * @return The queue of messages
   */
  [[nodiscard]] std::vector<payload::ChatMessage> ExtractChatQueue();

  /**
   * @brief Register a shoot
   * @param payload The shoot payload
   * @return true if the packet is sent, false otherwise
   */
  [[nodiscard]] bool Shoot(const payload::Shoot &payload);

  /**
   * @brief Register a movement
   * @param payload The movement payload
   * @return true if the packet is sent, false otherwise
   */
  [[nodiscard]] bool Move(const payload::Movement &payload);

  /**
   * @brief Refresh the game and rooms infos
   * @param game Refresh the game infos
   * @param rooms Refresh the rooms infos
   * @return true if the packet is sent, false otherwise
   */
  [[nodiscard]] bool RefreshInfos(bool game, bool rooms);

  /**
   * @brief Resolve players state from a server message
   * @param message The server message (available when extract the queue)
   * @return The list of player states
   */
  [[nodiscard]] std::vector<payload::PlayerState> ResolvePlayersState(const ServerMessage &message);

  /**
   * @brief Resolve enemies state from a server message
   * @param message The server message (available when extract the queue)
   * @return The list of enemies states
   */
  [[nodiscard]] std::vector<payload::EnemyState> ResolveEnemiesState(const ServerMessage &message);

  /**
   * @brief Resolve bullets state from a server message
   * @param message The server message (available when extract the queue)
   * @return The list of bullets states
   */
  [[nodiscard]] std::vector<payload::BulletState> ResolveBulletsState(const ServerMessage &message);

  /**
   * @brief Resolve the game infos from a server message
   * @param message The server message (available when extract the queue)
   * @return The game infos
   */
  [[nodiscard]] payload::InfoGame ResolveGameInfo(const ServerMessage &message);

  /**
   * @brief Resolve the rooms infos from a server message
   * @param message The server message (available when extract the queue)
   * @return The rooms infos
   */
  [[nodiscard]] payload::InfoRooms ResolveInfoRooms(const ServerMessage &message);

  /**
   * @brief Resolve the room game end from a server message
   * @param message The server message (available when extract the queue)
   * @return The room game end
   */
  [[nodiscard]] payload::GameEnd ResolveRoomGameEnd(const ServerMessage &message);

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
  void InitUDP(std::string ip, unsigned int port, unsigned int localPort);

  /**
   * @brief Start the UDP connection (run the IO contexte)
   */
  void ListenUDP();

  /**
   * @brief Initialize the chat TCP connection
   */
  void InitChatTCP(std::string ip, unsigned int port);

  /**
   * @brief Start the chat TCP connection (run the IO service)
   */
  void ListenChatTCP();

  /**
   * @brief Send a payload to the server TCP
   * @tparam T The payload type
   * @param type The message type
   * @param payload The payload to send
   * @return true if the packet is sent, false otherwise
   */
  template <typename T>
  bool SendPayloadTCP(const ClientToMasterMsgType &type, const T &payload);

  /**
   * @brief Send a payload to the server UDP
   * @tparam T The payload type
   * @param type The message type
   * @param payload The payload to send
   * @return true if the packet is sent, false otherwise
   */
  template <typename T>
  bool SendPayloadUDP(const ClientToRoomMsgType &type, const T &payload);

  /**
   * @brief Resolve payloads from a room message
   * @tparam T The payload type
   * @param type The message type to resolve
   * @param message The server message
   * @return The list of payloads
   */
  template <typename T>
  std::vector<T> ResolveUDPPayloads(RoomToClientMsgType type, const ServerMessage &message);

  /**
   * @brief Resolve payloads from a master message
   * @tparam T The payload type
   * @param type The message type to resolve
   * @param message The server message
   * @return The list of payloads
   */
  template <typename T>
  std::vector<T> ResolveTCPPayloads(MasterToClientMsgType type, const ServerMessage &message);

  /**
   * @brief Wait for a message from the server
   * @param type The message type to wait for
   * @param handler The handler to call when the message is received
   * @return true if the message is received and handled, false otherwise
   */
  bool WaitForMessage(MasterToClientMsgType type,
                      bool (Client::*handler)(const abra::tools::MessageProps &message));

  /**
   * @brief Handle TCP connection confirmation
   */
  bool HandleConnectionConfirmation(const abra::tools::MessageProps &);

  /**
   * @brief Handle Join lobby and init UDP connection
   * @param message The message with the lobby infos
   */
  bool HandleJoinLobbyInfos(const abra::tools::MessageProps &message);

  /**
   * @brief Convert a abra queue to generic server messages queue
   * @param queue The abra queue
   * @param serverQueue The server messages queue
   * @param protocolType The protocol type of the messages
   */
  static void ConvertQueueData(std::queue<abra::tools::MessageProps> *queue,
                               std::queue<ServerMessage> *serverQueue,
                               NetworkProtocolType protocolType);

  /// @brief The ABRA Client TCP instance (main connection)
  abra::client::ClientTCP clientTCP_;

  /// @brief The ABRA Client TCP instance (chat connection)
  std::optional<abra::client::ClientTCP> chatTCP_;

  /// @brief The ABRA Client UDP instance (specific game connection)
  /// @warning The UDP connection is used for the game only, it's not initialized by default
  std::optional<abra::client::ClientUDP> clientUDP_;

  /// @brief Packet builder
  abra::tools::PacketBuilder packetBuilder_;

  /// @brief The thread to listen the server (TCP)
  std::thread threadTCP_;

  /// @brief The thread to listen the server (UDP)
  std::thread threadUDP_;

  /// @brief The thread to listen the chat server (TCP)
  std::thread threadChatTCP_;

  /// @brief Boolean to know if the client is connected to the server
  /// @warning It's a r-type protocol information, it's not related to the TCP connection
  bool isConnected_;

  /// @brief Boolean to know if the client is connected to the lobby
  bool isLobbyConnected_;

  /// @brief Logger
  abra::tools::Logger logger_;
};

#include "libs/game/src/api/client/client.tpp"
