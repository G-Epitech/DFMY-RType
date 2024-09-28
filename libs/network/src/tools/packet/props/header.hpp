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
constexpr std::uint8_t kPacketHeaderPropsSize =
        kPacketHeaderPayloadLengthSize + kPacketHeaderPayloadTypeSize + kPacketHeaderFlagSize * 2;

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
    unsigned payloadLength: kPacketHeaderPayloadLengthSize = 0;  // 0..1023  (10 bits)
    unsigned payloadType: kPacketHeaderPayloadTypeSize = 0;      // 0..15    (4 bits)
    unsigned offsetFlag: kPacketHeaderFlagSize = 0;              // 0..1     (1 bit)
    unsigned turnFlag: kPacketHeaderFlagSize = 0;                // 0..1     (1 bit)
  };
}  // namespace rtype::sdk::network::tools
