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

  this->header_.offsetFlag = false;
  this->header_.payloadLength = sizeof(payload);
  this->message_.messageId = GeneratePacketId();

  auto packet = Packet<T>(this->header_, this->message_, payload, PacketOffsetProps(), this->turn_);

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

  this->header_.offsetFlag = true;
  this->header_.payloadLength = sizeof(payloads[0]);
  this->message_.messageId = GeneratePacketId();

  auto packets = std::vector<Packet < T>>
  ();
  auto offsetProps = PacketOffsetProps();

  for (auto &payload: payloads) {
    if (sizeof(payload) != sizeof(payloads[0]))
      throw Exception("Protocol error: Payloads are not the same size.");

    if (offsetProps.offset == payloads.size() - 1)
      offsetProps.offsetFlag = true;

    packets.push_back(Packet<T>(this->header_, this->message_, payload, offsetProps, this->turn_));
    offsetProps.offset++;
  }

  return packets;
}

template<typename T>
tools::Packet<T> tools::PacketBuilder::Build(const tools::dynamic_bitset &bitset) {
  if (bitset.GetSize() < kPacketHeaderPropsSize + kPacketMessagePropsSize)
    throw Exception("Protocol error: Bitset is too small.");
}
