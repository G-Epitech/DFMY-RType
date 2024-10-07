/*
** EPITECH PROJECT, 2024
** message.h
** File description:
** message class
*/

#pragma once

#include <cstdint>
#include "tools/bitset/dynamic_bitset.hpp"

struct ClientMessage {
  std::uint64_t clientId;
  unsigned int messageType;
  unsigned int messageId;
  std::shared_ptr<abra::tools::dynamic_bitset> bitset;
};
