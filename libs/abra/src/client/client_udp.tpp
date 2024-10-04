/*
** EPITECH PROJECT, 2024
** client_udp.hpp
** File description:
** ClientUDP class
*/

#pragma once

using namespace abra::client;

template<typename T>
SendMessageStatus ClientUDP::send(const std::unique_ptr<tools::Packet<T>> &packet) {
  auto bitset = packet->GetBitset();
  auto vector = bitset->GetVector();
  auto status = SendMessageStatus::SUCCESS;

  try {
    std::size_t len = this->socket_.send_to(boost::asio::buffer(vector, vector.size()), this->receiverEndpoint_);

    if (len != vector.size()) {
      status = SendMessageStatus::ERROR;
    }
  } catch (const std::exception &e) {
    status = SendMessageStatus::ERROR;
  }

  return status;
}
