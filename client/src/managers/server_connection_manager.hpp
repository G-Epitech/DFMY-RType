/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** window_manager.hpp
*/

#pragma once

#include <list>
#include <memory>
#include <optional>

#include "libs/game/src/api/client/client.hpp"

namespace rtype::client {
class ServerConnectionManager {
 public:
  /// @brief Pointer to a server connection manager
  typedef std::shared_ptr<ServerConnectionManager> Ptr;

  struct Properties {
    std::string ip;      ///< IP of the server
    std::uint32_t port;  ///< Port of the server
  };

  /**
   * @brief Create a new server connection manager
   * @param props Properties of the server connection
   * @return Pointer to the server connection manager
   */
  static Ptr Create(Properties &&props);

  /**
   * @brief Construct a new Server Connection Manager object
   * @param props Properties of the server connection
   */
  explicit ServerConnectionManager(Properties &&props);

  /**
   * @brief Destruct a Server Connection Manager object
   */
  ~ServerConnectionManager();

  /**
   * @brief Get the client object
   */
  inline api::Client::Ptr client() { return client_; }

  /**
   * @brief Try to connect to the server
   * @return True if the connection is successful, false otherwise
   */
  void ConnectAsync();

  /**
   * @brief Check if the client is connected
   * @return True if the client is connected, false otherwise
   */
  [[nodiscard]] bool Connected() const;

 private:
  enum class ConnectionStatus {
    kDisconnected,  ///< Disconnected
    kConnecting,    ///< Connecting
    kConnected,     ///< Connected
  };

  /**
   * @brief Connect to the server
   */
  void Connect();

  /// @brief To protect the client
  std::mutex clientMutex_;

  /// @brief Current client
  api::Client::Ptr client_;

  /// @brief Properties of the server connection
  Properties props_;

  /// @brief Connection thread
  std::thread connectionThread_;

  /// @brief Connection status
  ConnectionStatus connectionStatus_ = ConnectionStatus::kDisconnected;

  /// @brief Next retry time
  std::chrono::time_point<std::chrono::system_clock> nextRetry_;
};
}  // namespace rtype::client
