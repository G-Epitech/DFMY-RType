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
   * @brief Payload types for the packet header
   */
  enum class PayloadType {
    kCustom = 0,
    kCharacter = 1,
    kInt8 = 2,
    kUint8 = 3,
    kInt16 = 4,
    kUint16 = 5,
    kInt32 = 6,
    kUint32 = 7,
    kFloat = 8,
    kDouble = 9,
  };

  /**
   * @brief Packet header properties
   * @warning Do not exceed the maximum values delimited in bits
   */
  struct PacketHeaderProps {
    std::uint16_t payloadLength = 0;                // 10 bits, do not exceed 1023
    PayloadType payloadType = PayloadType::kCustom; // 4 bits, do not exceed 15
    bool offsetFlag = false;                        // 1 bit
    bool turnFlag = false;                          // 1 bit
  };
}
