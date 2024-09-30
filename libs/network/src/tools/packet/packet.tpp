/*
** EPITECH PROJECT, 2024
** packet.tpp
** File description:
** Packet class
*/

#pragma once

using namespace rtype::sdk::network;

template<typename T>
tools::Packet<T>::Packet(
        tools::PacketHeaderProps header,
        tools::PacketMessageProps message,
        T payload,
        tools::PacketOffsetProps offset,
        tools::PacketTurnProps turn) {
  this->mHeader = header;
  this->mMessage = message;
  this->mOffset = offset;
  this->mTurn = turn;
  this->mPayload = payload;

  if (!OffsetIsEnabled() && mOffset.offset > 0)
    throw tools::Packet<T>::Exception("Offset is not enabled in the header.");
  if (!TurnIsEnabled() && mTurn.turn > 0)
    throw tools::Packet<T>::Exception("Turn is not enabled in the header.");
}

template<typename T>
tools::Packet<T>::~Packet() = default;

template<typename T>
bool tools::Packet<T>::OffsetIsEnabled() const {
  return this->mHeader.offsetFlag == 1;
}

template<typename T>
bool tools::Packet<T>::TurnIsEnabled() const {
  return this->mHeader.turnFlag == 1;
}

template<typename T>
const tools::PacketHeaderProps &tools::Packet<T>::GetHeader() const {
  return this->mHeader;
}

template<typename T>
const tools::PacketMessageProps &tools::Packet<T>::GetMessage() const {
  return this->mMessage;
}

template<typename T>
const tools::PacketOffsetProps &tools::Packet<T>::GetOffset() const {
  if (!OffsetIsEnabled())
    throw tools::Packet<T>::Exception("Offset is not enabled for this packet.");
  return this->mOffset;
}

template<typename T>
const tools::PacketTurnProps &tools::Packet<T>::GetTurn() const {
  if (!TurnIsEnabled())
    throw tools::Packet<T>::Exception("Turn is not enabled for this packet.");
  return this->mTurn;
}

template<typename T>
const T &tools::Packet<T>::GetPayload() const {
  return this->mPayload;
}

template<typename T>
tools::Packet<T>::Exception::Exception(std::string message) : mMessage(std::move(message)) {}

template<typename T>
const char *tools::Packet<T>::Exception::what() const noexcept {
  return this->mMessage.c_str();
}

template<typename T>
std::shared_ptr<tools::dynamic_bitset> tools::Packet<T>::GetBitset() const {
  unsigned int bitsetSize = kPacketHeaderPropsSize + kPacketMessagePropsSize;
  if (OffsetIsEnabled())
    bitsetSize += kPacketOffsetPropsSize;
  if (TurnIsEnabled())
    bitsetSize += kPacketTurnPropsSize;

  bitsetSize += sizeof(this->mPayload) * 8;

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
void tools::Packet<T>::AppendHeaderToBitset(const std::shared_ptr<dynamic_bitset>& bitset, std::size_t *offset) const {
  bitset->Append(mHeader.payloadLength, kPacketHeaderPayloadLengthSize, *offset);
  *offset += kPacketHeaderPayloadLengthSize;

  bitset->Append(mHeader.payloadType, kPacketHeaderPayloadTypeSize, *offset);
  *offset += kPacketHeaderPayloadTypeSize;

  bitset->Append(mHeader.offsetFlag, kPacketHeaderFlagSize, *offset);
  *offset += kPacketHeaderFlagSize;

  bitset->Append(mHeader.turnFlag, kPacketHeaderFlagSize, *offset);
  *offset += kPacketHeaderFlagSize;
}

template<typename T>
void tools::Packet<T>::AppendMessageToBitset(const std::shared_ptr<dynamic_bitset>& bitset, std::size_t *offset) const {
  bitset->Append(mMessage.messageId, kPacketMessageIdSize, *offset);
  *offset += kPacketMessageIdSize;

  bitset->Append(mMessage.messageType, kPacketMessageTypeSize, *offset);
  *offset += kPacketMessageTypeSize;

  *offset += kPacketMessageVoidSize;
}

template<typename T>
void tools::Packet<T>::AppendOffsetToBitset(const std::shared_ptr<dynamic_bitset>& bitset, std::size_t *offset) const {
  if (!OffsetIsEnabled())
    return;

  bitset->Append(mOffset.offset, kPacketOffsetSize, *offset);
  *offset += kPacketOffsetSize;

  bitset->Append(mOffset.offsetFlag, kPacketOffsetSize, *offset);
  *offset += kPacketOffsetFlagSize;
}

template<typename T>
void tools::Packet<T>::AppendTurnToBitset(const std::shared_ptr<dynamic_bitset>& bitset, std::size_t *offset) const {
  if (!TurnIsEnabled())
    return;

  bitset->Append(mTurn.turn, kPacketTurnSize, *offset);
  *offset += kPacketTurnSize;
}

template<typename T>
void tools::Packet<T>::AppendPayloadToBitset(const std::shared_ptr<dynamic_bitset>& bitset, const std::size_t *offset) const {
  for (std::size_t i = 0; i < sizeof(this->mPayload) * 8; i++) {
    bitset->Set(*offset + i, (mPayload >> i) & 1);
  }
}
