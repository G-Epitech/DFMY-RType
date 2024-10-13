/*
** EPITECH PROJECT, 2024
** client_udp.hpp
** File description:
** ClientUDP class
*/

#pragma once

using namespace abra::client;

template<typename T>
tools::SendMessageStatus ClientUDP::Send(const std::unique_ptr<tools::Packet<T>> &packet) {
  const auto bitset = packet->GetBitset();
  const auto vector = bitset->GetVector();
  auto status = tools::SendMessageStatus::kSuccess;

  try {
    std::size_t len = this->socket_.send_to(boost::asio::buffer(vector, vector.size()), this->receiverEndpoint_);

    if (len != vector.size()) {
      status = tools::SendMessageStatus::kError;

      logger_.Error("Failed to send " + std::to_string(vector.size()) + " bytes", "➡️ ");
    }
  } catch (const std::exception &e) {
    status = tools::SendMessageStatus::kError;

    logger_.Error("Failed to send " + std::to_string(vector.size()) + " bytes. " + std::string(e.what()), "➡️ ");
  }

  if (status == tools::SendMessageStatus::kSuccess) {
    logger_.Info("Sent " + std::to_string(vector.size()) + " bytes", "➡️ ");
  }

  return status;
}
