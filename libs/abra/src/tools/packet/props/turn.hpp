/*
** EPITECH PROJECT, 2024
** turn.hpp
** File description:
** turn class
*/

#pragma once

#include <cstdint>

constexpr std::uint8_t kPacketTurnSize = 16;
constexpr std::uint8_t kPacketTurnPropsSize = kPacketTurnSize;

namespace abra::tools {
struct PacketTurnProps {
  unsigned turn : kPacketTurnSize = 0;  // 0..65535 (16 bits)
};
}  // namespace abra::tools
