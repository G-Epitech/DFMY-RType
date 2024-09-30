/*
** EPITECH PROJECT, 2024
** packet_builder.tpp
** File description:
** PacketBuilder class
*/

#pragma once

using namespace rtype::sdk::network;

template<typename T>
tools::Packet<T> tools::PacketBuilder::Build(T payload) {
  if (!IsValidBitSize(sizeof(payload), kPacketHeaderPayloadLengthSize))
    throw Exception("Invalid structure: Payload length is too big.");

  this->mHeader.offsetFlag = false;
  this->mHeader.payloadLength = sizeof(payload);
  this->mMessage.messageId = GeneratePacketId();

  auto packet = Packet<T>(this->mHeader, this->mMessage, payload, PacketOffsetProps(), this->mTurn);

  this->Reset();
  return packet;
}

template<typename T>
std::vector<tools::Packet<T>> tools::PacketBuilder::Build(std::vector<T> payloads) {
  if (!IsValidBitSize(payloads.size(), kPacketOffsetSize))
    throw Exception("Invalid structure: Vector size is too big.");
  if (payloads.size() == 0)
    throw Exception("Invalid structure: Vector size is empty.");
  if (!IsValidBitSize(sizeof(payloads[0]), kPacketHeaderPayloadLengthSize))
    throw Exception("Invalid structure: Payload length is too big.");

  this->mHeader.offsetFlag = true;
  this->mHeader.payloadLength = sizeof(payloads[0]);
  this->mMessage.messageId = GeneratePacketId();

  auto packets = std::vector<Packet < T>>
  ();
  auto offsetProps = PacketOffsetProps();

  for (auto &payload: payloads) {
    if (sizeof(payload) != sizeof(payloads[0]))
      throw Exception("Protocol error: Payloads are not the same size.");

    if (offsetProps.offset == payloads.size() - 1)
      offsetProps.offsetFlag = true;

    packets.push_back(Packet<T>(this->mHeader, this->mMessage, payload, offsetProps, this->mTurn));
    offsetProps.offset++;
  }

  return packets;
}

template<typename T>
tools::Packet<T> tools::PacketBuilder::Build(const tools::dynamic_bitset &bitset) {
  if (bitset.GetSize() < kPacketHeaderPropsSize + kPacketMessagePropsSize)
    throw Exception("Protocol error: Bitset is too small.");
}
