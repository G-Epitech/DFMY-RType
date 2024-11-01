/*
** EPITECH PROJECT, 2024
** message.hpp
** File description:
** message class
*/

#pragma once

#include <memory>
#include <optional>

#include "libs/abra/src/tools/bitset/dynamic_bitset.hpp"

namespace abra::tools {
/// @brief Enum for the status of the message
enum class SendMessageStatus {
  kSuccess = 0,  // The message was sent successfully
  kError = 1,    // An error occurred while sending the message
};

/// @brief Structure of a server message
struct MessageProps {
  unsigned int messageId;                             // ID of the message
  unsigned int messageType;                           // Type of the message
  std::shared_ptr<abra::tools::dynamic_bitset> data;  // Data of the message (bitset)
};

/// @brief Structure of a server message
struct MultipleMessageProps {
  unsigned int messageId;                             // ID of the message
  unsigned int messageType;                           // Type of the message
  unsigned int offset;                                // Offset of the message
  bool isLast;                                        // Is the last message
  std::shared_ptr<abra::tools::dynamic_bitset> data;  // Data of the message (bitset)
};

/// @brief Structure of multiple messages
struct MultipleMessagesProps {
  MultipleMessageProps* lastMessage = nullptr;  // The last message
  std::vector<MultipleMessageProps> messages;   // The messages
};
}  // namespace abra::tools
