/*
** EPITECH PROJECT, 2024
** room.hpp
** File description:
** Room class
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
class EXPORT_GAME_SDK_API Room;
}

class rtype::sdk::game::api::Room {
 public:
  /**
   * @brief Construct a new Room API instance
   * @param nodeIp The IP of the node.
   * @param nodePort The port of the node.
   * @param newPlayerHandler The handler to call when a new player is connected
   * @param roomId The room id
   */
  explicit Room(const std::string &nodeIp, std::size_t nodePort,
                const std::function<void(std::uint64_t)> &newPlayerHandler, std::uint64_t roomId);

  /**
   * @brief Delete the Room API instance
   */
  ~Room();

  struct RoomClient {
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
   * @brief Send state of players to all clients in a room
   * @param state The state of the players
   * @return true if the message is sent
   */
  bool SendPlayersState(const std::vector<payload::PlayerState> &state);

  /**
   * @brief Send state of players to all clients in a room
   * @param state The state of the players
   * @return true if the message is sent
   */
  bool SendEnemiesState(const std::vector<payload::EnemyState> &state);

  /**
   * @brief Send state of players to all clients in a room
   * @param state The state of the players
   * @return true if the message is sent
   */
  bool SendBulletsState(const std::vector<payload::BulletState> &state);

  /**
   * @brief Send start game message to all clients in a room
   * @return true if the message is sent
   */
  bool StartGame();

  /**
   * @brief Send end game message to all clients in a room
   * @param score The score of the player
   * @param time The time of the game
   * @param win The win state of the player
   * @return true if the message is sent
   */
  bool EndGame(unsigned int score, time_t time, bool win);

 private:
  /**
   * @brief Initialize the node thread
   */
  void InitNodeThread();

  /**
   * @brief Initialize the node thread
   */
  void InitClientsThread();

  /**
   * @brief Find a user by its endpoint
   * @param endpoint The endpoint to find
   * @return The user id
   */
  std::uint64_t FindUserByEndpoint(const boost::asio::ip::udp::endpoint &endpoint);

  /**
   * @brief Send message to node
   * @tparam T The type of the payload
   * @param type The type of the message
   * @param payload The payload to send
   */
  template <typename T>
  bool SendToNode(RoomToNodeMsgType type, const T &payload);

  /**
   * @brief Send message to all clients in the room
   * @tparam T The type of the payload
   * @param type The type of the message
   * @param payload The payload to send
   */
  template <typename T>
  bool SendToClients(RoomToClientMsgType type, const T &payload);

  /**
   * @brief Middleware to handle node messages
   * @param message The message of the node (NodeToRoomMsgType)
   * @return True if the message must be push in the queue of messages
   */
  bool NodeMessageMiddleware(const abra::tools::MessageProps &message);

  /**
   * @brief Handle the player join
   * @param message The message of the node
   */
  void HandlePlayerJoin(const abra::tools::MessageProps &message);

  /// @brief Server socket to communicate with clients (TCP)
  abra::client::ClientTCP nodeSocket_;

  /// @brief The thread that will run the clients socket
  std::thread nodeThread_;

  /// @brief Server socket to communicate with clients (UDP)
  abra::server::ServerUDP clientsSocket_;

  /// @brief The thread that will run the clients socket
  std::thread clientsThread_;

  /// @brief Logger
  abra::tools::Logger logger_;

  /// @brief Packet builder
  abra::tools::PacketBuilder packetBuilder_;

  /// @brief Handler to call when a new player is connected
  std::function<void(std::uint64_t)> newPlayerHandler_;

  /// @brief Clients in the room
  std::vector<RoomClient> clients_;

  /// @brief Room id
  std::uint64_t roomId_;

  static inline std::map<unsigned int, void (Room::*)(const abra::tools::MessageProps &message)>
      nodeMessageHandlers_ = {
          {NodeToRoomMsgType::kMsgTypeNTRPlayerJoin, &Room::HandlePlayerJoin},
  };
};

#include "room.tpp"
