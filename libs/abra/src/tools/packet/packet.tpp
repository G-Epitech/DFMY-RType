/*
** EPITECH PROJECT, 2024
** packet.tpp
** File description:
** Packet class
*/

#pragma once

#include <cstddef>
#include "packet_utils.hpp"

using namespace abra;

template<typename T>
tools::Packet<T>::Packet(
        tools::PacketHeaderProps header,
        tools::PacketMessageProps message,
        T payload,
        tools::PacketOffsetProps offset,
        tools::PacketTurnProps turn) {
  this->header_ = header;
  this->message_ = message;
  this->offset_ = offset;
  this->turn_ = turn;
  this->payload_ = payload;

  if (!OffsetIsEnabled() && offset_.offset > 0)
    throw tools::Packet<T>::Exception("Offset is not enabled in the header.");
  if (!TurnIsEnabled() && turn_.turn > 0)
    throw tools::Packet<T>::Exception("Turn is not enabled in the header.");
}

template<typename T>
tools::Packet<T>::~Packet() = default;

template<typename T>
bool tools::Packet<T>::OffsetIsEnabled() const {
  return this->header_.offsetFlag == 1;
}

template<typename T>
bool tools::Packet<T>::TurnIsEnabled() const {
  return this->header_.turnFlag == 1;
}

template<typename T>
const tools::PacketHeaderProps &tools::Packet<T>::GetHeader() const {
  return this->header_;
}

template<typename T>
const tools::PacketMessageProps &tools::Packet<T>::GetMessage() const {
  return this->message_;
}

template<typename T>
const tools::PacketOffsetProps &tools::Packet<T>::GetOffset() const {
  if (!OffsetIsEnabled())
    throw tools::Packet<T>::Exception("Offset is not enabled for this packet.");
  return this->offset_;
}

template<typename T>
const tools::PacketTurnProps &tools::Packet<T>::GetTurn() const {
  if (!TurnIsEnabled())
    throw tools::Packet<T>::Exception("Turn is not enabled for this packet.");
  return this->turn_;
}

template<typename T>
const T &tools::Packet<T>::GetPayload() const {
  return this->payload_;
}

template<typename T>
tools::Packet<T>::Exception::Exception(std::string message) : mMessage(std::move(message)) {}

template<typename T>
const char *tools::Packet<T>::Exception::what() const noexcept {
  return this->mMessage.c_str();
}

template<typename T>
std::shared_ptr<tools::dynamic_bitset> tools::Packet<T>::GetBitset() {
  unsigned int bitsetSize = kPacketHeaderPropsSize + kPacketMessagePropsSize;
  if (OffsetIsEnabled())
    bitsetSize += kPacketOffsetPropsSize;
  if (TurnIsEnabled())
    bitsetSize += kPacketTurnPropsSize;

  bitsetSize += sizeof(this->payload_) * 8;

  std::shared_ptr<dynamic_bitset> bitset = std::make_shared<dynamic_bitset>(bitsetSize);
  std::size_t offset = 0;

  AppendHeaderToBitset(bitset, &offset);
  AppendMessageToBitset(bitset, &offset);
  AppendOffsetToBitset(bitset, &offset);
  AppendTurnToBitset(bitset, &offset);
  AppendPayloadToBitset(bitset, &offset);

  return bitset;
}

template<typename T>
void tools::Packet<T>::AppendHeaderToBitset(const std::shared_ptr<dynamic_bitset> &bitset, std::size_t *offset) const {
  bitset->Append(header_.payloadLength, kPacketHeaderPayloadLengthSize, *offset);
  *offset += kPacketHeaderPayloadLengthSize;

  bitset->Append(header_.payloadType, kPacketHeaderPayloadTypeSize, *offset);
  *offset += kPacketHeaderPayloadTypeSize;

  bitset->Append(header_.offsetFlag, kPacketHeaderFlagSize, *offset);
  *offset += kPacketHeaderFlagSize;

  bitset->Append(header_.turnFlag, kPacketHeaderFlagSize, *offset);
  *offset += kPacketHeaderFlagSize;
}

template<typename T>
void tools::Packet<T>::AppendMessageToBitset(const std::shared_ptr<dynamic_bitset> &bitset, std::size_t *offset) const {
  bitset->Append(message_.messageId, kPacketMessageIdSize, *offset);
  *offset += kPacketMessageIdSize;

  bitset->Append(message_.messageType, kPacketMessageTypeSize, *offset);
  *offset += kPacketMessageTypeSize;

  *offset += kPacketMessageVoidSize;
}

template<typename T>
void tools::Packet<T>::AppendOffsetToBitset(const std::shared_ptr<dynamic_bitset> &bitset, std::size_t *offset) const {
  if (!OffsetIsEnabled())
    return;

  bitset->Append(offset_.offset, kPacketOffsetSize, *offset);
  *offset += kPacketOffsetSize;

  bitset->Append(offset_.offsetFlag, kPacketOffsetFlagSize, *offset);
  *offset += kPacketOffsetFlagSize;
}

template<typename T>
void tools::Packet<T>::AppendTurnToBitset(const std::shared_ptr<dynamic_bitset> &bitset, std::size_t *offset) const {
  if (!TurnIsEnabled())
    return;

  bitset->Append(turn_.turn, kPacketTurnSize, *offset);
  *offset += kPacketTurnSize;
}

template<typename T>
void tools::Packet<T>::AppendPayloadToBitset(const std::shared_ptr<dynamic_bitset> &bitset, std::size_t *offset) {
  auto *payloadMemory = reinterpret_cast<char *>(&payload_);

  for (std::size_t i = 0; i < sizeof(payload_); i++) {
    unsigned byte = static_cast<unsigned char>(payloadMemory[i]);

    bitset->Append(byte, 8, *offset);
    *offset += 8;
  }
}
