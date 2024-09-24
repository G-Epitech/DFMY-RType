/*
** EPITECH PROJECT, 2024
** messages.hpp
** File description:
** messages class
*/

#pragma once

#include <cstdint>

constexpr std::uint8_t kPacketMessageIdSize = 20;
constexpr std::uint8_t kPacketMessageTypeSize = 6;

namespace rtype::sdk::network::tools {
  struct PacketMessageProps {
    unsigned messageId: kPacketMessageIdSize = 0;     // 0..1048575 (20 bits)
    unsigned messageType: kPacketMessageTypeSize = 0; // 0..63      (6 bits)
    unsigned : 6;
  };
}
