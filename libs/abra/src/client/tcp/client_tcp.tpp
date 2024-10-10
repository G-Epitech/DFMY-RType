/*
** EPITECH PROJECT, 2024
** client_tcp.tpp
** File description:
** ClientTCP class
*/

#pragma once

using namespace abra::client;

template<typename T>
tools::SendMessageStatus ClientTCP::Send(const std::unique_ptr<tools::Packet<T>> &packet) {
  const auto bitset = packet->GetBitset();
  const auto vector = bitset->GetVector();

  boost::system::error_code error;
  this->socket_.write_some(boost::asio::buffer(vector, vector.size()), error);

  logger_.Info("Sent " + std::to_string(vector.size()) + " bytes", "➡️ ");

  return error ? tools::SendMessageStatus::kError : tools::SendMessageStatus::kSuccess;
}
