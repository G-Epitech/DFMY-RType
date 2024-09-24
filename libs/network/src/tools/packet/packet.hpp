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
  template<typename T>
  class EXPORT_NETWORK_SDK_API Packet;
}

template<typename T>
class EXPORT_NETWORK_SDK_API rtype::sdk::network::tools::Packet {
public:
  /**
   * @brief Construct a new Packet object
   * @param header Header properties
   * @param message Message properties
   * @param payload Payload related to packet type
   * @param offset Offset properties (default: empty)
   * @param turn Turn properties (default: empty)
   */
  Packet(PacketHeaderProps header, PacketMessageProps message, T payload,
         PacketOffsetProps offset = PacketOffsetProps(),
         PacketTurnProps turn = PacketTurnProps());

  ~Packet();

  /**
   * @brief Check if the offset is enabled in the header
   * @return true if the offset flag is enabled (bit to 1)
   */
  [[nodiscard]] bool OffsetIsEnabled() const;

  /**
   * @brief Check if the turn is enabled in the header
   * @return true if the turn flag is enabled (bit to 1)
   */
  [[nodiscard]] bool TurnIsEnabled() const;

private:
  PacketHeaderProps mHeader;    // Packet header properties
  PacketMessageProps mMessage;  // Packet message properties
  PacketOffsetProps mOffset;    // Packet offset properties
  PacketTurnProps mTurn;        // Packet turn properties
  T mPayload;                   // Packet payload
};

#include "packet.tpp"
