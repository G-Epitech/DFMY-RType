/*
** EPITECH PROJECT, 2024
** client_udp.hpp
** File description:
** ClientUDP class
*/

#pragma once

template <typename T>
abra::tools::SendMessageStatus abra::client::ClientUDP::Send(
    const std::unique_ptr<abra::tools::Packet<T>> &packet) {
  const auto bitset = packet->GetBitset();
  const auto vector = bitset->GetVector();
  auto status = abra::tools::SendMessageStatus::kSuccess;

  try {
    std::size_t len =
        this->socket_.send_to(boost::asio::buffer(vector, vector.size()), this->receiverEndpoint_);

    if (len != vector.size()) {
      status = abra::tools::SendMessageStatus::kError;
    }
  } catch (const std::exception &e) {
    status = abra::tools::SendMessageStatus::kError;
  }

  return status;
}
