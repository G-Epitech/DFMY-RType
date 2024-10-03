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
class EXPORT_NETWORK_SDK_API InterfaceClient;
}  // namespace abra::client

class EXPORT_NETWORK_SDK_API abra::client::InterfaceClient {
 public:
  enum class SendMessageStatus {
    SUCCESS,
    ERROR,
  };

  InterfaceClient() = delete;

  ~InterfaceClient() = delete;

  /**
   * @brief Listen the server and handle the incoming data
   */
  virtual void listen() = 0;

  /**
   * @brief Send a message to the server
   * @return The message queue
   */
  [[nodiscard]] virtual const std::queue<ServerMessage> &getQueue() const = 0;

 private:
  std::queue<ServerMessage> queue_;
};
