/*
** EPITECH PROJECT, 2024
** header.hpp
** File description:
** header class
*/

#pragma once

#include <cstdint>

constexpr std::uint8_t kPacketHeaderPayloadLengthSize = 10;
constexpr std::uint8_t kPacketHeaderPayloadTypeSize = 4;
constexpr std::uint8_t kPacketHeaderFlagSize = 1;

namespace rtype::sdk::network::tools {
  /**
   * @brief Packet header properties
   * @warning Do not exceed the maximum values delimited in bits
   */
  struct PacketHeaderProps {
    std::uint16_t payloadLength = 0;    // 10 bits, do not exceed 1023
    std::uint8_t payloadType = 0;       // 4 bits, do not exceed 15
    bool offsetFlag = false;            // 1 bit
    bool turnFlag = false;              // 1 bit
  };
}
