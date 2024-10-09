/*
** EPITECH PROJECT, 2024
** client.hpp
** File description:
** Client class
*/

#include <boost/asio.hpp>
#include <queue>

#include "../core.hpp"
#include "tools/message/message.hpp"
#include "tools/packet/packet.hpp"

#pragma once

namespace abra::client {
class EXPORT_NETWORK_SDK_API InterfaceClient;
}  // namespace abra::client

class abra::client::InterfaceClient {
 public:
  InterfaceClient() = default;

  /**
   * @brief Listen the server and handle the incoming data
   */
  virtual void Listen() = 0;

 protected:
  /**
   * @brief Resolve packets in a buffer
   * This method will split the buffer into logical packets with header props
   * @param buffer The buffer received
   */
  virtual void ResolveBuffer(std::vector<char> *buffer) = 0;

  /// @brief The queue of server messages
  std::queue<tools::MessageProps> queue_;
};
