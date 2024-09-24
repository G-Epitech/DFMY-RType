/*
** EPITECH PROJECT, 2024
** packet.hpp
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
tools::Packet<T>::Exception::Exception(std::string message) : mMessage(std::move(message)) {}

template<typename T>
const char *tools::Packet<T>::Exception::what() const noexcept {
  return this->mMessage.c_str();
}
