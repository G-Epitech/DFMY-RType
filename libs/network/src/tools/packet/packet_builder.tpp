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

  this->mHeader.offsetFlag = 0;
  this->mHeader.payloadLength = sizeof(payload);
  this->mMessage.messageId = GeneratePacketId();

  auto packet = Packet<T>(this->mHeader, this->mMessage, payload, this->mOffset, this->mTurn);

  this->Reset();
  return packet;
}
