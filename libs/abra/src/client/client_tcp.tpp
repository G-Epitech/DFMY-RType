/*
** EPITECH PROJECT, 2024
** client_tcp.tpp
** File description:
** ClientTCP class
*/

#pragma once

using namespace abra::client;

template<typename T>
SendMessageStatus ClientTCP::send(tools::Packet<T> *packet) {
  auto bitset = packet->GetBitset();
  auto vector = bitset->GetVector();

  boost::system::error_code error;
  this->socket_.write_some(boost::asio::buffer(vector, vector.size()), error);

  return error ? SendMessageStatus::ERROR : SendMessageStatus::SUCCESS;
}
