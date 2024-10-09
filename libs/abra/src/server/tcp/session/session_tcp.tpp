/*
** EPITECH PROJECT, 2024
** session_tcp.tpp
** File description:
** SessionTCP class
*/

#pragma once

using namespace abra::server;

template<typename T>
tools::SendMessageStatus SessionTCP::Send(const std::unique_ptr<tools::Packet<T>> &packet) {
  const auto bitset = packet->GetBitset();
  const auto vector = bitset->GetVector();

  boost::system::error_code error;
  this->socket_.write_some(boost::asio::buffer(vector, vector.size()), error);

  return error ? tools::SendMessageStatus::kError : tools::SendMessageStatus::kSuccess;
}
