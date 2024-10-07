/*
** EPITECH PROJECT, 2024
** message.h
** File description:
** message class
*/

#pragma once

#include <cstdint>
#include "tools/bitset/dynamic_bitset.hpp"

/// @brief A client message for TCP protocol
struct ClientMessage {
  std::uint64_t clientId;                               // Client ID
  unsigned int messageType;                             // Message type
  unsigned int messageId;                               // Message ID
  std::shared_ptr<abra::tools::dynamic_bitset> bitset;  // The bitset of the message
};
