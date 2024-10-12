/*
** EPITECH PROJECT, 2024
** client.hpp
** File description:
** Client class
*/

#include <boost/asio.hpp>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <vector>

#include "../core.hpp"
#include "tools/logger/logger.hpp"
#include "tools/message/message.hpp"
#include "tools/packet/packet.hpp"

#pragma once

namespace abra::client {
class EXPORT_NETWORK_SDK_API InterfaceClient;
}  // namespace abra::client

class abra::client::InterfaceClient {
 public:
  InterfaceClient() = default;

  virtual ~InterfaceClient() = default;

  /**
   * @brief Listen the server and handle the incoming data
   */
  virtual void Listen() = 0;

  /**
   * @brief Extract the queue of messages
   * @warning This method will clear the queue
   * @return The queue of messages
   */
  virtual std::queue<tools::MessageProps> ExtractQueue() = 0;

  /**
   * @brief Extract the queue of multi messages
   * @warning This method will clear the queue
   * @return The queue of multi messages
   */
  virtual std::queue<tools::MultipleMessagesProps> ExtractMultiQueue() = 0;

  /// @brief The mutex for the queue
  std::mutex Mutex;

 protected:
  /**
   * @brief Resolve packets in a buffer
   * This method will split the buffer into logical packets with header props
   * @param buffer The buffer received
   */
  virtual void ResolveBuffer(std::vector<char> *buffer, std::size_t len) = 0;

  /**
   * @biref Handle bitset when there are an offset (multi packets)
   * @param bitset The bitset to handle
   */
  virtual void HandleMultiPacketsBitset(std::shared_ptr<tools::dynamic_bitset> bitset) = 0;

  /// @brief The queue of server messages
  std::queue<tools::MessageProps> queue_;

  /// @brief The queue of multi packets
  std::queue<tools::MultipleMessagesProps> multiPackets_;

  /// @brief The map of messages for multi packets
  std::map<unsigned, tools::MultipleMessagesProps> pendingMultiPackets_;
};
