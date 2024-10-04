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
/// @brief Enum for the status of the message
enum class SendMessageStatus {
  kSuccess = 0,  // The message was sent successfully
  kError = 1,    // An error occurred while sending the message
};

/// @brief Structure of a server message
struct ServerMessage {
  unsigned int messageId;                             // ID of the message
  unsigned int messageType;                           // Type of the message
  std::shared_ptr<abra::tools::dynamic_bitset> data;  // Data of the message (bitset)
};
}  // namespace abra::client
