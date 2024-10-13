/*
** EPITECH PROJECT, 2024
** server_udp.tpp
** File description:
** ServerUDP class
*/

#pragma once


template<typename T>
abra::tools::SendMessageStatus
abra::server::ServerUDP::Send(const std::unique_ptr<abra::tools::Packet<T>> &packet, const boost::asio::ip::udp::endpoint &endpoint) {
  const auto bitset = packet->GetBitset();
  const auto vector = bitset->GetVector();
  auto status = abra::tools::SendMessageStatus::kSuccess;

  // debug endpoint
  std::cout << endpoint.address().to_string() << ":" << endpoint.port() << std::endl;

  try {
    std::size_t len = this->socket_.send_to(boost::asio::buffer(vector, vector.size()), endpoint);

    if (len != vector.size()) {
      status = tools::SendMessageStatus::kError;

      logger_.Error("Failed to send " + std::to_string(vector.size()) + " bytes", "➡️ ");
    }
  } catch (const std::exception &e) {
    status = abra::tools::SendMessageStatus::kError;

    logger_.Error("Failed to send " + std::to_string(vector.size()) + " bytes. " + std::string(e.what()), "➡️ ");
  }

  if (status == abra::tools::SendMessageStatus::kSuccess) {
    logger_.Info("Sent " + std::to_string(vector.size()) + " bytes", "➡️ ");
  }

  return status;
}
