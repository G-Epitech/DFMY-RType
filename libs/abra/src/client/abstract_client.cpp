/*
** EPITECH PROJECT, 2024
** abstract_client.cpp
** File description:
** AbstractClient class
*/

#include "./abstract_client.hpp"

#include "libs/abra/src/tools/packet/packet_utils.hpp"

using namespace abra::client;

AbstractClient::AbstractClient(const std::string &name) : logger_(name) {}

void client::AbstractClient::ResolveBuffer(std::vector<char> *buffer, std::size_t len) {
  if (buffer->size() < kPacketHeaderPropsSize / 8) {
    return;
  }

  auto bitset = std::make_shared<tools::dynamic_bitset>(*buffer);
  auto header = tools::PacketUtils::ExportHeaderFromBitset(bitset);
  std::size_t packetSize = (kPacketHeaderPropsSize + kPacketMessagePropsSize) / 8;

  if (header.offsetFlag) {
    packetSize += kPacketOffsetPropsSize / 8;
  }
  if (header.turnFlag) {
    packetSize += kPacketTurnPropsSize / 8;
  }
  packetSize += header.payloadLength;

  if (packetSize == len) {
    return StoreMessage(bitset, header.offsetFlag);
  }

  logger_.Info("Receive too bigger packet (" + std::to_string(len) + " bytes) than expected (" +
               std::to_string(packetSize) + " bytes)");

  if (packetSize > len) {
    return;
  }

  std::vector<char> cleanBuffer(
      buffer->begin(),
      buffer->begin() + static_cast<std::vector<char>::difference_type>(packetSize));
  auto cleanBitset = std::make_shared<tools::dynamic_bitset>(*buffer);

  StoreMessage(cleanBitset, header.offsetFlag);

  buffer->erase(buffer->begin(),
                buffer->begin() + static_cast<std::vector<char>::difference_type>(packetSize));
  return ResolveBuffer(buffer, len - packetSize);
}

void AbstractClient::HandleMultiPacketsBitset(std::shared_ptr<tools::dynamic_bitset> bitset) {
  auto messageId = tools::PacketUtils::ExportMessageIdFromBitset(bitset);
  auto offset = tools::PacketUtils::ExportOffsetFromBitset(bitset);

  if (pendingMultiPackets_.find(messageId) == pendingMultiPackets_.end()) {
    pendingMultiPackets_[messageId] = tools::MultipleMessagesProps();
  }

  tools::MultipleMessageProps message = {
      .messageId = messageId,
      .messageType = tools::PacketUtils::ExportMessageTypeFromBitset(bitset),
      .offset = offset.offset,
      .isLast = offset.offsetFlag == 1,
      .data = bitset,
  };
  pendingMultiPackets_[messageId].messages.push_back(message);
  if (message.isLast) {
    pendingMultiPackets_[messageId].lastMessage = &pendingMultiPackets_[messageId].messages.back();
  }

  logger_.Info("Store a part of multi packet with type " + std::to_string(message.messageType) +
               " and offset " + std::to_string(offset.offset));

  ResolveMultiPackets(messageId);
}

void AbstractClient::StoreMessage(std::shared_ptr<tools::dynamic_bitset> bitset, bool hasOffset) {
  if (hasOffset) {
    HandleMultiPacketsBitset(bitset);
  } else {
    tools::MessageProps message = {tools::PacketUtils::ExportMessageIdFromBitset(bitset),
                                   tools::PacketUtils::ExportMessageTypeFromBitset(bitset), bitset};
    logger_.Info("Store message with type " + std::to_string(message.messageType));

    std::unique_lock<std::mutex> lock(this->Mutex);
    this->queue_.push(message);
  }
}

void AbstractClient::ResolveMultiPackets(unsigned int messageId) {
  if (pendingMultiPackets_[messageId].lastMessage.has_value() &&
      pendingMultiPackets_[messageId].messages.size() ==
          pendingMultiPackets_[messageId].lastMessage.value()->offset + 1) {
    std::sort(pendingMultiPackets_[messageId].messages.begin(),
              pendingMultiPackets_[messageId].messages.end(),
              [](const tools::MultipleMessageProps &a, const tools::MultipleMessageProps &b) {
                return a.offset < b.offset;
              });

    this->multiPackets_.push(pendingMultiPackets_[messageId]);
    pendingMultiPackets_.erase(messageId);

    logger_.Info("Resolve multi packet with id " + std::to_string(messageId));
  }
}

std::queue<tools::MessageProps> AbstractClient::ExtractQueue() {
  std::unique_lock<std::mutex> lock(this->Mutex);

  auto queue = this->queue_;
  this->queue_ = std::queue<tools::MessageProps>();

  return queue;
}

std::queue<tools::MultipleMessagesProps> AbstractClient::ExtractMultiQueue() {
  std::unique_lock<std::mutex> lock(this->Mutex);

  auto queue = this->multiPackets_;
  this->multiPackets_ = std::queue<tools::MultipleMessagesProps>();

  return queue;
}
