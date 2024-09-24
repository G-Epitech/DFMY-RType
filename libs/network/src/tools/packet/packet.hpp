/*
** EPITECH PROJECT, 2024
** packet.hpp
** File description:
** Packet class
*/

#pragma once

#include "api.hpp"
#include "props/props.hpp"

namespace rtype::sdk::network::tools {
  class EXPORT_NETWORK_SDK_API Packet;
}

class EXPORT_NETWORK_SDK_API rtype::sdk::network::tools::Packet {
public:
  Packet();

  ~Packet();

private:
  PacketHeaderProps mHeader; // Packet header properties
  PacketMessageProps mMessage; // Packet message properties
  PacketOffsetProps mOffset; // Packet offset properties
  PacketTurnProps mTurn; // Packet turn properties
};
