/*
** EPITECH PROJECT, 2024
** packet_utils.cpp
** File description:
** PacketUtils class
*/

#include "packet_utils.hpp"

#include "packet.hpp"

using namespace abra;

unsigned tools::PacketUtils::ExportMessageTypeFromBitset(
    const std::shared_ptr<dynamic_bitset> &bitset) {
  unsigned messageType = 0;
  std::size_t startRange = kPacketHeaderPropsSize + kPacketMessageIdSize;

  bitset->FillFromRange(startRange, startRange + kPacketMessageTypeSize, &messageType);
  return messageType;
}

unsigned tools::PacketUtils::ExportMessageIdFromBitset(
    const std::shared_ptr<dynamic_bitset> &bitset) {
  unsigned messageId = 0;
  std::size_t startRange = kPacketHeaderPropsSize;

  bitset->FillFromRange(startRange, startRange + kPacketMessageIdSize, &messageId);
  return messageId;
}

tools::PacketHeaderProps tools::PacketUtils::ExportHeaderFromBitset(
    const std::shared_ptr<dynamic_bitset> &bitset) {
  unsigned value = 0;
  auto props = tools::PacketHeaderProps();
  std::size_t startRange = 0;

  bitset->FillFromRange(startRange, startRange + kPacketHeaderPayloadLengthSize, &value);
  props.payloadLength = value;
  value = 0;
  startRange += kPacketHeaderPayloadLengthSize;

  bitset->FillFromRange(startRange, startRange + kPacketHeaderPayloadTypeSize, &value);
  props.payloadType = value;
  value = 0;
  startRange += kPacketHeaderPayloadTypeSize;

  bitset->FillFromRange(startRange, startRange + kPacketHeaderFlagSize, &value);
  props.offsetFlag = value;
  value = 0;
  startRange += kPacketHeaderFlagSize;

  bitset->FillFromRange(startRange, startRange + kPacketHeaderFlagSize, &value);
  props.turnFlag = value;

  return props;
}
