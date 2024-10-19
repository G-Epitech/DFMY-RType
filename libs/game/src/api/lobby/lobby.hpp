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
   */
  explicit Lobby(int port);

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
   * @brief Extract queue of messages
   * @warning The queue is cleared after the extraction
   * @param id The lobby id
   * @return The queue of messages
   */
  [[nodiscard]] std::queue<std::pair<std::uint64_t, abra::server::ClientUDPMessage>> ExtractQueue(
      std::uint64_t id);

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
  /// @brief The ABRA Server TCP instance
  abra::server::ServerTCP serverTCP_;

  /// @brief The TCP thread
  std::thread threadTCP_;

  /// @brief The ABRA Server UDP instance for game communication
  abra::server::ServerUDP serverUDP_;

  /// @brief The UDP thread
  std::thread threadUDP_;

  /// @brief The list of clients connected to the lobby
  std::vector<LobbyClient> clients;

  /// @brief The logger
  abra::tools::Logger logger_;
};
