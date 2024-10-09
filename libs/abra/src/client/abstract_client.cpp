/*
** EPITECH PROJECT, 2024
** abstract_client.cpp
** File description:
** AbstractClient class
*/

#include "abstract_client.hpp"

#include "tools/packet/packet_utils.hpp"

using namespace abra::client;

void client::AbstractClient::ResolveBuffer(std::vector<char> *buffer) {
  if (buffer->size() < kPacketHeaderPropsSize / 8) {
    return;
  }

  auto bitset = std::make_shared<tools::dynamic_bitset>(*buffer);
  auto header = tools::PacketUtils::ExportHeaderFromBitset(bitset);
  std::size_t packetSize = (kPacketHeaderPropsSize + kPacketMessagePropsSize) / 8;

  if (header.offsetFlag)
    packetSize += kPacketOffsetPropsSize / 8;
  if (header.turnFlag)
    packetSize += kPacketTurnPropsSize / 8;
  packetSize += header.payloadLength;

  if (packetSize == buffer->size()) {
    if (header.offsetFlag) {
      HandleMultiPacketsBitset(bitset);
    } else {
      tools::MessageProps message = {tools::PacketUtils::ExportMessageTypeFromBitset(bitset),
                                     tools::PacketUtils::ExportMessageIdFromBitset(bitset), bitset};
      queue_.push(message);
    }
    return;
  }

  if (packetSize > buffer->size()) {
    return;
  }

  std::vector<char> cleanBuffer(
      buffer->begin(),
      buffer->begin() + static_cast<std::vector<char>::difference_type>(packetSize));
  auto cleanBitset = std::make_shared<tools::dynamic_bitset>(*buffer);

  if (header.offsetFlag) {
    HandleMultiPacketsBitset(cleanBitset);
  } else {
    tools::MessageProps message = {tools::PacketUtils::ExportMessageTypeFromBitset(cleanBitset),
                                   tools::PacketUtils::ExportMessageIdFromBitset(cleanBitset),
                                   cleanBitset};
    queue_.push(message);
  }

  buffer->erase(buffer->begin(),
                buffer->begin() + static_cast<std::vector<char>::difference_type>(packetSize));
  return ResolveBuffer(buffer);
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
  }
}
