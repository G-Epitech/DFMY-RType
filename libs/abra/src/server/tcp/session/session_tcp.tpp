/*
** EPITECH PROJECT, 2024
** session_tcp.tpp
** File description:
** SessionTCP class
*/

#pragma once

template <typename T>
abra::tools::SendMessageStatus abra::server::SessionTCP::Send(
    const std::unique_ptr<abra::tools::Packet<T>> &packet) {
  const auto bitset = packet->GetBitset();
  const auto vector = bitset->GetVector();

  boost::system::error_code error;
  this->socket_.write_some(boost::asio::buffer(vector, vector.size()), error);

  logger_.Info("Sent " + std::to_string(vector.size()) + " bytes", "➡️ ");

  return error ? abra::tools::SendMessageStatus::kError : abra::tools::SendMessageStatus::kSuccess;
}
