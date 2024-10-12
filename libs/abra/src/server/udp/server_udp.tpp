/*
** EPITECH PROJECT, 2024
** server_udp.tpp
** File description:
** ServerUDP class
*/

#pragma once


template<typename T>
abra::tools::SendMessageStatus
abra::server::ServerUDP::Send(const std::shared_ptr<abra::tools::Packet<T>> &packet, const boost::asio::ip::udp::endpoint &endpoint) {
  const auto bitset = packet->GetBitset();
  const auto vector = bitset->GetVector();
  auto status = abra::tools::SendMessageStatus::kSuccess;

  try {
    std::size_t len = this->socket_.send_to(boost::asio::buffer(vector, vector.size()), endpoint);

    if (len != vector.size()) {
      status = abra::tools::SendMessageStatus::kError;
    }
  } catch (const std::exception &e) {
    status = abra::tools::SendMessageStatus::kError;
  }

  return status;
}
