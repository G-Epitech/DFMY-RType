/*
** EPITECH PROJECT, 2024
** turn.hpp
** File description:
** turn class
*/

#pragma once

#include <cstdint>

constexpr std::uint8_t kPacketTurnSize = 16;

namespace rtype::sdk::network::tools {
struct PacketTurnProps {
  unsigned turn : kPacketTurnSize = 0;  // 0..65535 (16 bits)
};
}  // namespace rtype::sdk::network::tools
