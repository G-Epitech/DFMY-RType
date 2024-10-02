/*
** EPITECH PROJECT, 2024
** offset.hpp
** File description:
** offset class
*/

#pragma once

#include <cstdint>

constexpr std::uint8_t kPacketOffsetSize = 15;
constexpr std::uint8_t kPacketOffsetFlagSize = 1;
constexpr std::uint8_t kPacketOffsetPropsSize = kPacketOffsetSize + kPacketOffsetFlagSize;

namespace abra::tools {
struct PacketOffsetProps {
  unsigned offset : kPacketOffsetSize = 0;          // 0..32767 (15 bits)
  unsigned offsetFlag : kPacketOffsetFlagSize = 0;  // 0..1 (1 bit)
};
}  // namespace abra::tools
