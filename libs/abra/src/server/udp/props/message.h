/*
** EPITECH PROJECT, 2024
** message.h
** File description:
** message class
*/

#pragma once

#include <boost/asio.hpp>

#include "tools/bitset/dynamic_bitset.hpp"

/// @brief A client message for UDP protocol
struct ClientMessage {
  boost::asio::ip::udp::endpoint endpoint;              // The endpoint of the client
  unsigned int messageType;                             // Message type
  unsigned int messageId;                               // Message ID
  std::shared_ptr<abra::tools::dynamic_bitset> bitset;  // The bitset of the message
};
