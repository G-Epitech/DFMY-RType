/*
** EPITECH PROJECT, 2024
** server_tcp.tpp
** File description:
** ServerTCP class
*/

#pragma once

using namespace abra::server;

template<typename T>
tools::SendMessageStatus
ServerTCP::Send(const std::unique_ptr<tools::Packet<T>> &packet, const std::uint64_t &clientId) {
  auto client = clients_[clientId];

  if (!client) {
    return tools::SendMessageStatus::kError;
  }
  return client->Send<T>(packet);
}
