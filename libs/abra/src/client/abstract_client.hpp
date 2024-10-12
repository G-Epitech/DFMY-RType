/*
** EPITECH PROJECT, 2024
** abstract_client.hpp
** File description:
** AbstractClient class
*/

#pragma once

#include "../core.hpp"
#include "interface_client.hpp"

namespace abra::client {
class EXPORT_NETWORK_SDK_API AbstractClient;
}  // namespace abra::client

class abra::client::AbstractClient : public abra::client::InterfaceClient {
 public:
  explicit AbstractClient(const std::string &name);

  /**
   * @brief Extract the queue of messages
   * @warning This method will clear the queue
   * @return The queue of messages
   */
  std::queue<tools::MessageProps> ExtractQueue() override;

  /**
   * @brief Extract the queue of multi messages
   * @warning This method will clear the queue
   * @return The queue of multi messages
   */
  std::queue<tools::MultipleMessagesProps> ExtractMultiQueue() override;

 protected:
  /**
   * @brief Resolve packets in a buffer
   * This method will split the buffer into logical packets with header props
   * @param buffer The buffer received
   */
  void ResolveBuffer(std::vector<char> *buffer, std::size_t len) override;

  /**
   * @biref Handle bitset when there are an offset (multi packets)
   * @param bitset The bitset to handle
   */
  void HandleMultiPacketsBitset(std::shared_ptr<tools::dynamic_bitset> bitset) override;

  /// @brief Logger
  tools::Logger logger_;

 private:
  void StoreMessage(std::shared_ptr<tools::dynamic_bitset> bitset, bool hasOffset);

  void ResolveMultiPackets(unsigned int messageId);
};
