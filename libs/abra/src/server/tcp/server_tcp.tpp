/*
** EPITECH PROJECT, 2024
** server_tcp.tpp
** File description:
** ServerTCP class
*/

#pragma once


template<typename T>
abra::tools::SendMessageStatus
abra::server::ServerTCP::Send(const std::unique_ptr<abra::tools::Packet<T>> &packet, const std::uint64_t &clientId) {
  auto client = clients_[clientId];

  if (!client) {
    return abra::tools::SendMessageStatus::kError;
  }
  return client->Send<T>(packet);
}
