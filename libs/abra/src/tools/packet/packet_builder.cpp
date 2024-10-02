/*
** EPITECH PROJECT, 2024
** packet_builder.cpp
** File description:
** PacketBuilder class
*/

#include "packet_builder.hpp"

#include <valarray>

using namespace abra;

tools::PacketBuilder::PacketBuilder() : message_() {
  this->Reset();
  this->packetIdIncrement_ = 0;
}

tools::PacketBuilder::~PacketBuilder() {
  this->Reset();
}

tools::PacketBuilder::Exception::Exception(std::string message) {
  this->mMessage = std::move(message);
  this->mMessage = "PacketBuilder exception: " + this->mMessage;
}

const char *tools::PacketBuilder::Exception::what() const noexcept {
  return this->mMessage.c_str();
}

void tools::PacketBuilder::Reset() {
  header_ = PacketHeaderProps();
  message_ = PacketMessageProps();
  turn_ = PacketTurnProps();
}

tools::PacketBuilder &tools::PacketBuilder::SetPayloadType(tools::PayloadType payloadType) {
  auto castType = static_cast<unsigned>(payloadType);

  if (!IsValidBitSize(castType, kPacketHeaderPayloadTypeSize))
    throw Exception("Invalid argument: Payload type is out of range.");

  this->header_.payloadType = castType;
  return *this;
}

tools::PacketBuilder &tools::PacketBuilder::SetTurn(std::uint16_t turn) {
  if (!IsValidBitSize(turn, kPacketTurnSize))
    throw Exception("Invalid argument: Turn is out of range.");

  this->turn_.turn = turn;
  this->header_.turnFlag = 1;
  return *this;
}

tools::PacketBuilder &tools::PacketBuilder::SetMessageType(std::uint8_t messageType) {
  if (!IsValidBitSize(messageType, kPacketMessageTypeSize))
    throw Exception("Invalid argument: Message too much AGA");

  this->message_.messageType = messageType;
  return *this;
}

bool tools::PacketBuilder::IsValidBitSize(unsigned int value, std::uint8_t bitSize) {
  return value < std::pow(2, bitSize);
}

std::uint32_t tools::PacketBuilder::GeneratePacketId() {
  const auto maxId = std::pow(2, kPacketMessageIdSize) - 1;
  const auto generatedId = this->packetIdIncrement_;

  this->packetIdIncrement_ = (this->packetIdIncrement_ + 1);
  if (this->packetIdIncrement_ > maxId)
    this->packetIdIncrement_ = 0;

  return generatedId;
}

void tools::PacketBuilder::SetHeaderFromBitset(const std::shared_ptr<dynamic_bitset> &bitset,
                                               std::size_t *offset) {
  unsigned int payloadLength = 0;
  unsigned int payloadType = 0;
  unsigned int offsetFlag = 0;
  unsigned int turnFlag = 0;

  bitset->FillFromRange(*offset, *offset + kPacketHeaderPayloadLengthSize, &payloadLength);
  *offset += kPacketHeaderPayloadLengthSize;

  bitset->FillFromRange(*offset, *offset + kPacketHeaderPayloadTypeSize, &payloadType);
  *offset += kPacketHeaderPayloadTypeSize;

  bitset->FillFromRange(*offset, *offset + kPacketHeaderFlagSize, &offsetFlag);
  *offset += kPacketHeaderFlagSize;

  bitset->FillFromRange(*offset, *offset + kPacketHeaderFlagSize, &turnFlag);
  *offset += kPacketHeaderFlagSize;

  this->header_.payloadLength = payloadLength;
  this->header_.payloadType = payloadType;
}

void tools::PacketBuilder::SetMessageFromBitset(const std::shared_ptr<dynamic_bitset> &bitset,
                                                std::size_t *offset) {
  unsigned int messageId = 0;
  unsigned int messageType = 0;

  bitset->FillFromRange(*offset, *offset + kPacketMessageIdSize, &messageId);
  *offset += kPacketMessageIdSize;

  bitset->FillFromRange(*offset, *offset + kPacketMessageTypeSize, &messageType);
  *offset += kPacketMessageTypeSize;

  *offset += kPacketMessageVoidSize;

  this->message_.messageId = messageId;
  this->message_.messageType = messageType;
}

void tools::PacketBuilder::FillOffsetFromBitset(const std::shared_ptr<dynamic_bitset> &bitset,
                                                std::size_t *offset,
                                                PacketOffsetProps *offsetProps) {
  unsigned int offsetProp = 0;
  unsigned int offsetFlag = 0;

  bitset->FillFromRange(*offset, *offset + kPacketOffsetSize, &offsetProp);
  *offset += kPacketOffsetSize;

  bitset->FillFromRange(*offset, *offset + kPacketOffsetFlagSize, &offsetFlag);
  *offset += kPacketOffsetFlagSize;

  offsetProps->offset = offsetProp;
  offsetProps->offsetFlag = offsetFlag;
}

void tools::PacketBuilder::SetTurnFromBitset(const std::shared_ptr<dynamic_bitset> &bitset,
                                             std::size_t *offset) {
  unsigned int turn = 0;

  bitset->FillFromRange(*offset, *offset + kPacketTurnSize, &turn);
  *offset += kPacketTurnSize;

  this->turn_.turn = turn;
}
