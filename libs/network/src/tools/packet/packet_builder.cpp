/*
** EPITECH PROJECT, 2024
** packet_builder.cpp
** File description:
** PacketBuilder class
*/

#include <complex>
#include "packet_builder.hpp"

#include <valarray>

using namespace rtype::sdk::network;

tools::PacketBuilder::PacketBuilder(): mMessage() {
  this->mPacketIdIncrement = 0;
} ;

tools::PacketBuilder::~PacketBuilder() {
  this->Reset();
};

tools::PacketBuilder::Exception::Exception(std::string message) : mMessage(std::move(message)) {}

const char *tools::PacketBuilder::Exception::what() const noexcept {
  return ("PacketBuilder exception: " + mMessage).c_str();
}

void tools::PacketBuilder::Reset() {
  mHeader = PacketHeaderProps();
  mMessage = PacketMessageProps();
  mTurn = PacketTurnProps();
}

tools::PacketBuilder &tools::PacketBuilder::SetPayloadType(tools::PayloadType payloadType) {
  auto castType = static_cast<unsigned>(payloadType);

  if (!IsValidBitSize(castType, kPacketHeaderPayloadTypeSize))
    throw Exception("Invalid argument: Payload type is out of range.");

  this->mHeader.payloadType = castType;
  return *this;
}

tools::PacketBuilder &tools::PacketBuilder::SetTurn(std::uint16_t turn) {
  if (!IsValidBitSize(turn, kPacketTurnSize))
    throw Exception("Invalid argument: Turn is out of range.");

  this->mTurn.turn = turn;
  this->mHeader.turnFlag = 1;
  return *this;
}

tools::PacketBuilder &tools::PacketBuilder::SetMessageType(std::uint8_t messageType) {
  if (!IsValidBitSize(messageType, kPacketMessageTypeSize))
    throw Exception("Invalid argument: Message too much AGA");

  this->mMessage.messageType = messageType;
  return *this;
}

bool tools::PacketBuilder::IsValidBitSize(unsigned int value, std::uint8_t bitSize) {
  return value < std::pow(2, bitSize);
}

std::uint32_t tools::PacketBuilder::GeneratePacketId() {
  const auto maxId = std::pow(2, kPacketMessageIdSize) - 1;
  const auto generatedId = this->mPacketIdIncrement;

  this->mPacketIdIncrement = (this->mPacketIdIncrement + 1);
  if (this->mPacketIdIncrement > maxId)
    this->mPacketIdIncrement = 0;

  return generatedId;
}
