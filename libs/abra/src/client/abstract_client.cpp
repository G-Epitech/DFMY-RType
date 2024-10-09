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
    tools::MessageProps message = {tools::PacketUtils::ExportMessageTypeFromBitset(bitset),
                                   tools::PacketUtils::ExportMessageIdFromBitset(bitset), bitset};
    queue_.push(message);
    return;
  }

  if (packetSize > buffer->size()) {
    return;
  }

  std::vector<char> cleanBuffer(
      buffer->begin(),
      buffer->begin() + static_cast<std::vector<char>::difference_type>(packetSize));
  auto cleanBitset = std::make_shared<tools::dynamic_bitset>(*buffer);
  tools::MessageProps message = {tools::PacketUtils::ExportMessageTypeFromBitset(cleanBitset),
                                 tools::PacketUtils::ExportMessageIdFromBitset(cleanBitset),
                                 cleanBitset};
  queue_.push(message);

  buffer->erase(buffer->begin(),
                buffer->begin() + static_cast<std::vector<char>::difference_type>(packetSize));
  return ResolveBuffer(buffer);
}
