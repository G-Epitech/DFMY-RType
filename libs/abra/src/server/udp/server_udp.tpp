/*
** EPITECH PROJECT, 2024
** server_udp.tpp
** File description:
** ServerUDP class
*/

#pragma once

using namespace abra::server;

template<typename T>
tools::SendMessageStatus
ServerUDP::Send(const std::unique_ptr<tools::Packet<T>> &packet, const boost::asio::ip::udp::endpoint &endpoint) {
  const auto bitset = packet->GetBitset();
  const auto vector = bitset->GetVector();
  auto status = tools::SendMessageStatus::kSuccess;

  try {
    std::size_t len = this->socket_.send_to(boost::asio::buffer(vector, vector.size()), endpoint);

    if (len != vector.size()) {
      status = tools::SendMessageStatus::kError;
    }
  } catch (const std::exception &e) {
    status = tools::SendMessageStatus::kError;
  }

  return status;
}
