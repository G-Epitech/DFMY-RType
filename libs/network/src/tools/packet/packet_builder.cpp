/*
** EPITECH PROJECT, 2024
** packet_builder.cpp
** File description:
** PacketBuilder class
*/

#include "packet_builder.hpp"

#include <valarray>

using namespace rtype::sdk::network;

tools::PacketBuilder::PacketBuilder() : message_() {
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
