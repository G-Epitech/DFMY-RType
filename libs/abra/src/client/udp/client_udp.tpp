/*
** EPITECH PROJECT, 2024
** client_udp.hpp
** File description:
** ClientUDP class
*/

#pragma once

using namespace abra::client;

template<typename T>
SendMessageStatus ClientUDP::Send(const std::unique_ptr<tools::Packet<T>> &packet) {
  const auto bitset = packet->GetBitset();
  const auto vector = bitset->GetVector();
  auto status = SendMessageStatus::kSuccess;

  try {
    std::size_t len = this->socket_.send_to(boost::asio::buffer(vector, vector.size()), this->receiverEndpoint_);

    if (len != vector.size()) {
      status = SendMessageStatus::kError;
    }
  } catch (const std::exception &e) {
    status = SendMessageStatus::kError;
  }

  return status;
}
