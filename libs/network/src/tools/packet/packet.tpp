/*
** EPITECH PROJECT, 2024
** packet.hpp
** File description:
** Packet class
*/

#pragma once

template<typename T>
rtype::sdk::network::tools::Packet<T>::Packet(
        rtype::sdk::network::tools::PacketHeaderProps header,
        rtype::sdk::network::tools::PacketMessageProps message,
        T payload,
        rtype::sdk::network::tools::PacketOffsetProps offset,
        rtype::sdk::network::tools::PacketTurnProps turn) {
  this->mHeader = header;
  this->mMessage = message;
  this->mOffset = offset;
  this->mTurn = turn;
  this->mPayload = payload;
}

template<typename T>
rtype::sdk::network::tools::Packet<T>::~Packet() = default;

template<typename T>
bool rtype::sdk::network::tools::Packet<T>::OffsetIsEnabled() const {
  return this->mHeader.offsetFlag == 1;
}

template<typename T>
bool rtype::sdk::network::tools::Packet<T>::TurnIsEnabled() const {
  return this->mHeader.turnFlag == 1;
}
