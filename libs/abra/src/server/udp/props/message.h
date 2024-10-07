/*
** EPITECH PROJECT, 2024
** message.h
** File description:
** message class
*/

#pragma once

#include <boost/asio.hpp>

#include "tools/bitset/dynamic_bitset.hpp"

struct ClientMessage {
  boost::asio::ip::udp::endpoint endpoint;
  unsigned int messageType;
  unsigned int messageId;
  std::shared_ptr<abra::tools::dynamic_bitset> bitset;
};
