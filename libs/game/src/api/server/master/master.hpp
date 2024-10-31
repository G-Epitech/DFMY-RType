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
class EXPORT_GAME_SDK_API Master;
}

class rtype::sdk::game::api::Master {
 public:
  /**
   * @brief Construct a new Server API instance
   * @param clientsPort The port of the clients socket
   * @param nodesPort The port of the nodes socket
   */
  explicit Master(int clientsPort, int nodesPort);

  /**
   * @brief Delete the Server API instance
   */
  ~Master();

  struct Client {
    std::uint64_t id;
    std::string username;
    bool inRoom;
    std::uint64_t nodeId;
    std::uint64_t roomId;
  };

  struct Room {
    std::uint64_t id;
    std::string name;
    unsigned int maxPlayers;
    unsigned int nbPlayers;
    unsigned int difficulty;
    unsigned int port;
  };

  struct Node {
    std::uint64_t id;
    std::string name;
    std::size_t maxRooms;
    std::map<std::uint64_t, Room> rooms_;
  };

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
   * @brief Initialize the clients thread
   */
  void InitClientsThread();

  /**
   * @brief Initialize the nodes thread
   */
  void InitNodesThread();

  /**
   * @brief Send a payload to a specific client (TCP)
   * @tparam T The type of the payload
   * @param type The type of the message
   * @param payload The payload to send
   * @param clientId The client id
   * @return true if the message is sent
   */
  template <typename T>
  bool SendToClient(const MasterToClientMsgType &type, const T &payload,
                    const std::uint64_t &clientId);

  /**
   * @brief Send a payload to a specific node (TCP)
   * @tparam T The type of the payload
   * @param type The type of the message
   * @param payload The payload to send
   * @param lobbyId The lobby id
   * @return true if the message is sent
   */
  template <typename T>
  bool SendToNode(const MasterToNodeMsgType &type, const T &payload, const std::uint64_t &nodeId);

  /**
   * @brief Handle the incoming client TCP messages
   * @return true if the message must be added to the queue (false if the message is handled)
   */
  [[nodiscard]] bool ClientMessageMiddleware(const abra::server::ClientTCPMessage &message);

  /**
   * @brief Handle the incoming node TCP messages
   * @return true if the message must be added to the queue (false if the message is handled)
   */
  [[nodiscard]] bool NodeMessageMiddleware(const abra::server::ClientTCPMessage &message);

  /**
   * @brief Handle a client connection
   * @param message The message of the client
   */
  void HandleClientConnection(const abra::server::ClientTCPMessage &message);

  /**
   * @brief Handle refresh of infos
   * @param message The message of the client
   */
  void HandleRefreshInfos(const abra::server::ClientTCPMessage &message);

  /**
   * @brief Handle the creation of a room
   * @param message The message of the client
   */
  void HandleCreateRoom(const abra::server::ClientTCPMessage &message);

  /**
   * @brief Handle the join of a room
   * @param message The message of the client
   */
  void HandleJoinRoom(const abra::server::ClientTCPMessage &message);

  /**
   * @brief Handle the registration of a node
   * @param message The message of the node
   */
  void HandleRegisterNode(const abra::server::ClientTCPMessage &message);

  /**
   * @brief Handle the registration of a room
   * @param message The message of the node
   */
  void HandleRegisterRoom(const abra::server::ClientTCPMessage &message);

  /**
   * @brief Handle the start of a game in a room
   * @param message The message of the node
   */
  void HandleRoomGameStarted(const abra::server::ClientTCPMessage &message);

  /**
   * @brief Handle the end of a game in a room
   * @param message The message of the node
   */
  void HandleRoomGameEnded(const abra::server::ClientTCPMessage &message);

  /**
   * @brief Add a new client to the server
   * @param clientId The client id
   * @param pseudo The pseudo of the client
   */
  void AddNewClient(std::uint64_t clientId, const std::string &pseudo);

  /**
   * @brief Send infos about the game and rooms
   * @param clientId The client id
   * @param game Send game infos
   * @param rooms Send rooms infos
   */
  void SendInfos(std::uint64_t clientId, bool game, bool rooms);

  /**
   * @brief Send game infos
   */
  void SendGameInfos(std::uint64_t clientId);

  /**
   * @brief Send rooms infos
   */
  void SendRoomsInfos(std::uint64_t clientId);

  /**
   * @brief Send info about a room
   * @param clientId The client id
   * @param room The room
   * @param node The node
   */
  void SendInfoRoom(std::uint64_t clientId, const Room &room, const Master::Node &node);

  /**
   * @brief Send a player join to a node
   * @param nodeId The node id
   * @param client The client
   */
  void SendPlayerJoinToNode(const std::uint64_t &nodeId, const Client &client);

  /// @brief Server socket to communicate with clients (TCP)
  abra::server::ServerTCP clientsSocket_;

  /// @brief The thread that will run the clients socket
  std::thread clientsThread_;

  /// @brief Server socket to communicate with nodes (TCP)
  abra::server::ServerTCP nodesSocket_;

  /// @brief The thread that will run the nodes socket
  std::thread nodesThread_;

  /// @brief Packet builder
  abra::tools::PacketBuilder packetBuilder_;

  /// @brief The logger
  abra::tools::Logger logger_;

  /// @brief Vector of clients
  std::vector<Client> clients_;

  /// @brief Vector of nodes
  std::map<std::uint64_t, Node> nodes_;

  /// @brief Map of handlers for the TCP messages
  static inline std::map<unsigned int, void (Master::*)(const abra::server::ClientTCPMessage &)>
      clientMessageHandlers = {
          {ClientToMasterMsgType::kMsgTypeCTMConnect, &Master::HandleClientConnection},
          {ClientToMasterMsgType::kMsgTypeCTMRefreshInfos, &Master::HandleRefreshInfos},
          {ClientToMasterMsgType::kMsgTypeCTMCreateRoom, &Master::HandleCreateRoom},
          {ClientToMasterMsgType::kMsgTypeCTMJoinRoom, &Master::HandleJoinRoom},
  };

  /// @brief Map of handlers for the TCP messages
  static inline std::map<unsigned int, void (Master::*)(const abra::server::ClientTCPMessage &)>
      nodeMessageHandlers = {
          {NodeToMasterMsgType::kMsgTypeNTMRegisterNode, &Master::HandleRegisterNode},
          {NodeToMasterMsgType::kMsgTypeNTMRegisterNewRoom, &Master::HandleRegisterRoom},
          {NodeToMasterMsgType::kMsgTypeNTMRoomGameStarted, &Master::HandleRoomGameStarted},
          {NodeToMasterMsgType::kMsgTypeNTMRoomGameEnded, &Master::HandleRoomGameEnded},
  };
};

#include "master.tpp"
