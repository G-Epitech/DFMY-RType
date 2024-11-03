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

namespace rtype::client::services {
class ServerConnectionService {
 public:
  /// @brief Pointer to a server connection manager
  typedef std::shared_ptr<ServerConnectionService> Ptr;

  struct Properties {
    std::string ip;      ///< IP of the server
    std::uint32_t port;  ///< Port of the server
  };

  /**
   * @brief Construct a new Server Connection Service object
   * @param ip IP of the server
   * @param port Port of the server
   */
  ServerConnectionService(const std::string& ip, std::uint32_t port);

  /**
   * @brief Destruct a Server Connection Service object
   */
  ~ServerConnectionService();

  /**
   * @brief Get the client object
   */
  inline api::Client::Ptr client() { return client_; }

  /**
   * @brief Try to connect to the server
   * @param username Username to connect with*
   */
  void ConnectAsync(const std::string& username);

  /**
   * @brief Check if the client is connected
   * @return True if the client is connected, false otherwise
   */
  [[nodiscard]] bool Connected() const;

  enum class ConnectionStatus {
    kDisconnected,  ///< Disconnected
    kConnecting,    ///< Connecting
    kConnected,     ///< Connected
    kFailed,        ///< Failed to connect
  };

  /**
   * @brief Get the connection status
   * @return ConnectionStatus The connection status
   */
  [[nodiscard]] ConnectionStatus connectionStatus() const;

 private:
  /**
   * @brief Connect to the server
   * @param username Username to connect with
   */
  void Connect(const std::string& username);

  /// @brief To protect the client
  std::mutex clientMutex_;

  /// @brief Current client
  api::Client::Ptr client_;

  /// @brief Properties of the server connection
  Properties props_;

  /// @brief Connection thread
  std::optional<std::thread> connectionThread_;

  /// @brief Connection status
  ConnectionStatus connectionStatus_ = ConnectionStatus::kDisconnected;

  /// @brief Next retry time
  std::chrono::time_point<std::chrono::system_clock> nextRetry_;
};
}  // namespace rtype::client::services
