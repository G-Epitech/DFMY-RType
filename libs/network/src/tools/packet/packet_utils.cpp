/*
** EPITECH PROJECT, 2024
** packet_utils.cpp
** File description:
** PacketUtils class
*/

#include "packet_utils.hpp"
#include "packet.hpp"

unsigned rtype::sdk::network::tools::PacketUtils::ExportMessageTypeFromBitset(
        const rtype::sdk::network::tools::DynamicBitset &bitset) {
  unsigned messageType = 0;
  std::size_t startRange = kPacketHeaderPropsSize + kPacketMessageIdSize;

  bitset.FillFromRange(startRange, startRange + kPacketMessageTypeSize, messageType);
  return messageType;
}
