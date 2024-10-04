/*
** EPITECH PROJECT, 2024
** client.hpp
** File description:
** Client class
*/

#include <boost/asio.hpp>
#include <queue>

#include "api.hpp"
#include "props/message.hpp"
#include "tools/packet/packet.hpp"

#pragma once

namespace abra::client {
class EXPORT_NETWORK_SDK_API IClient;
}  // namespace abra::client

class abra::client::IClient {
 public:
  IClient() = default;

  /**
   * @brief Listen the server and handle the incoming data
   */
  virtual void listen() = 0;

  /**
   * @brief Send a message to the server
   * @return The message queue
   */
  [[nodiscard]] virtual const std::queue<ServerMessage> &getQueue() const = 0;

 protected:
  /// @brief The queue of server messages
  std::queue<ServerMessage> queue_;
};
