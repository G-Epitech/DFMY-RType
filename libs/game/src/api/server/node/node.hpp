/*
** EPITECH PROJECT, 2024
** node.hpp
** File description:
** node class
*/

#pragma once

#include <string>
#include <thread>
#include <vector>

#include "libs/abra/includes/network.hpp"
#include "libs/abra/includes/packet.hpp"
#include "libs/game/src/api/props/message.hpp"
#include "libs/game/src/api/props/payload/payload.hpp"
#include "libs/game/src/core.hpp"

namespace rtype::sdk::game::api {
class EXPORT_GAME_SDK_API Node;
}

class rtype::sdk::game::api::Node {
 public:
  /**
   * @brief Construct a new Node API object
   * @param name Name of the node
   * @param token Token to connect to the master
   * @param maxRooms Max room that the node can create
   */
  Node(std::string name, std::string token, std::size_t maxRooms, const std::string &masterIp,
       std::size_t masterPort);

  /**
   * @brief Destroy the Node API object
   */
  ~Node();

  /// @brief The props of a room
  struct RoomProps {
    uint64_t id;
    uint64_t socketId;
    std::string name;
    unsigned int maxPlayers;
    unsigned int nbPlayers;
    unsigned int difficulty;
  };

  /**
   * @brief Start the node and send register message to the master
   */
  void Start(
      const std::function<bool(std::uint64_t roomId, std::size_t maxPlayers, std::size_t difficulty,
                               unsigned int port)> &createRoomHandler);

  /**
   * @biref Wait the end of threads
   */
  void Join();

 private:
  /**
   * @brief Initialize the master thread
   */
  void InitMasterThread();

  /**
   * @brief Initialize the rooms thread
   */
  void InitRoomsThread();

  /**
   * @brief Send message to master
   * @tparam T The type of the payload
   * @param type Type of message
   * @param payload The payload
   * @return Success of the send
   */
  template <typename T>
  bool SendToMaster(NodeToMasterMsgType type, const T &payload);

  /**
   * @brief Send message to room
   * @tparam T The type of the payload
   * @param socketId The socket id of the room
   * @param type Type of message
   * @param payload The payload
   * @return Success of the send
   */
  template <typename T>
  bool SendToRoom(std::uint64_t socketId, NodeToRoomMsgType type, const T &payload);

  /**
   * @brief Register the node to the master
   * @return Success of the registration
   */
  bool RegisterToMaster();

  /**
   * @brief Register a new room from a room call
   * @param socketId The room socket id
   * @param registerPayload The payload of the room
   */
  void RegisterNewRoom(uint64_t socketId, const payload::RegisterRoom &registerPayload);

  /**
   * @brief Middleware to handle master messages
   * @param message The message of the master (MasterToNodeMsgType)
   * @return True if the message must be push in the queue of messages
   */
  bool MasterMessageMiddleware(const abra::tools::MessageProps &message);

  /**
   * @brief Middleware to handle rooms messages
   * @param message The message of the room (RoomToNodeMsgType)
   * @return True if the message must be push in the queue of messages
   */
  bool RoomsMessageMiddleware(const abra::server::ClientTCPMessage &message);

  /**
   * @brief Handle room creation
   * @param message The message of the master (MasterToNodeMsgType::kMsgTypeMTNCreateRoom)
   */
  void HandleRoomCreation(const abra::tools::MessageProps &message);

  /**
   * @brief Handle new player join a room
   * @param message The message of the master (MasterToNodeMsgType::kMsgTypeMTNPlayerJoin)
   */
  void HandlePlayerJoin(const abra::tools::MessageProps &message);

  /**
   * @brief Handle new room register
   * @param message The message of the room (RoomToNodeMsgType::kMsgTypeRTNRegisterRoom)
   */
  void HandleRoomRegister(const abra::server::ClientTCPMessage &message);

  /**
   * @brief Handle a game started
   * @param message The message of the room (RoomToNodeMsgType::kMsgTypeRTNGameStarted)
   */
  void HandleGameStarted(const abra::server::ClientTCPMessage &message);

  /**
   * @brief Handle a game ended
   * @param message The message of the room (RoomToNodeMsgType::kMsgTypeRTNGameEnded)
   */
  void HandleGameEnded(const abra::server::ClientTCPMessage &message);

  /**
   * @brief Execute the logic of the end of a game
   * @param endPayload The end payload
   * @param room The room props
   */
  void EndGame(const payload::GameEnd &endPayload, const RoomProps &room);

  /**
   * @brief Find a room by id
   * @param id The id of the room
   * @return The room props
   */
  RoomProps &FindRoomById(std::uint64_t id);

  /**
   * @brief Find a room by socket id
   * @param id The socket id of the room
   * @return The room props
   */
  RoomProps &FindRoomBySocketId(std::uint64_t id);

  /**
   * @brief Remove a room by id
   * @param id The id of the room
   */
  void RemoveRoom(std::uint64_t id);

  /// @brief Name of the node
  std::string name_;

  /// @brief Token to connect to the master
  std::string token_;

  /// @brief Max room that the node can create
  std::size_t maxRooms_;

  /// @brief Client socket to communicate with the master (TCP)
  abra::client::ClientTCP masterSocket_;

  /// @brief Thread to handle the master socket
  std::thread masterThread_;

  /// @brief Server socket to communicate with rooms (TCP)
  abra::server::ServerTCP roomsSocket_;

  /// @brief Thread to handle the rooms socket
  std::thread roomsThread_;

  /// @brief Vector of rooms props
  std::vector<RoomProps> rooms_;

  /// @brief Logger
  abra::tools::Logger logger_;

  /// @brief Packet builder
  abra::tools::PacketBuilder packetBuilder_;

  /// @brief Last lobby id
  std::uint64_t lastRoomId_;

  /// @brief Creation of room handler
  std::function<bool(std::uint64_t roomId, std::size_t maxPlayers, std::size_t difficulty,
                     unsigned int port)>
      createRoomHandler_;

  static inline std::map<unsigned int, void (Node::*)(const abra::tools::MessageProps &message)>
      masterMessageHandlers_ = {
          {MasterToNodeMsgType::kMsgTypeMTNCreateRoom, &Node::HandleRoomCreation},
          {MasterToNodeMsgType::kMsgTypeMTNPlayerJoinRoom, &Node::HandlePlayerJoin},
  };

  static inline std::map<unsigned int,
                         void (Node::*)(const abra::server::ClientTCPMessage &message)>
      roomMessageHandlers_ = {
          {RoomToNodeMsgType::kMsgTypeRTNRegisterRoom, &Node::HandleRoomRegister},
          {RoomToNodeMsgType::kMsgTypeRTNGameStarted, &Node::HandleGameStarted},
          {RoomToNodeMsgType::kMsgTypeRTNGameEnded, &Node::HandleGameEnded},
  };
};

#include "./node.tpp"
