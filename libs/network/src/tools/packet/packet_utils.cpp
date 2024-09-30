/*
** EPITECH PROJECT, 2024
** packet_utils.cpp
** File description:
** PacketUtils class
*/

#include "packet_utils.hpp"

#include "packet.hpp"

using namespace rtype::sdk::network;

unsigned tools::PacketUtils::ExportMessageTypeFromBitset(
    const std::shared_ptr<dynamic_bitset> &bitset) {
  unsigned messageType = 0;
  std::size_t startRange = kPacketHeaderPropsSize + kPacketMessageIdSize;

  bitset->FillFromRange(startRange, startRange + kPacketMessageTypeSize, messageType);
  return messageType;
}
