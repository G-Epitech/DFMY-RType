/*
** EPITECH PROJECT, 2024
** message.hpp
** File description:
** message class
*/

#pragma once

#include <memory>

#include "tools/bitset/dynamic_bitset.hpp"

namespace abra::client {
struct ServerMessage {
  unsigned int messageId;
  unsigned int messageType;
  std::shared_ptr<abra::tools::dynamic_bitset> data;
};
}  // namespace abra::client
