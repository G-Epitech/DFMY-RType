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
#include "libs/game/src/core.hpp"
#include "libs/game/src/api/props/payload/payload.hpp"
#include "libs/game/src/api/props/message.hpp"

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
    std::size_t maxPlayers;
    std::size_t nbPlayers;
    unsigned int difficulty;
  };

  /**
   * @brief Start the node and send register message to the master
   */
  void Start();

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
  template<typename T>
  bool SendToMaster(NodeToMasterMsgType type, const T &payload);

  /**
   * @brief Register the node to the master
   * @return Success of the registration
   */
  bool RegisterToMaster();

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
};

#include "./node.tpp"
