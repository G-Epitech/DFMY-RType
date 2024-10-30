/*
** EPITECH PROJECT, 2024
** network.hpp
** File description:
** network class
*/

#pragma once

constexpr const char *kIpNull = "0.0.0.0";
constexpr const char *kLocalhost = "127.0.0.1";
constexpr unsigned int kClientUDPPort = 3480;

namespace rtype::sdk::game::api {
/// @brief Network protocol type
enum class NetworkProtocolType { kTCP, kUDP };
}  // namespace rtype::sdk::game::api
