/*
** EPITECH PROJECT, 2024
** client.tpp
** File description:
** client class
*/

#pragma once

using namespace rtype::sdk::game::api;
using namespace abra::tools;

template <typename T>
bool Client::SendPayload(const MessageClientType &type, const T &payload) {
  this->packetBuilder_.SetMessageType(type).SetPayloadType(PayloadType::kCustom);
  auto packet = this->packetBuilder_.Build(payload);

  return this->clientTCP_.Send(packet) == SendMessageStatus::kSuccess;
}

template <>
bool Client::WaitForMessage<NetworkProtocolType::kTCP>(
        MessageServerType type, bool (Client::*handler)(const tools::MessageProps &message)) {
  std::size_t timeout = kServerResponseTimeout;
  MessageProps message;
  bool success = false;

  while (timeout > 0) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    timeout -= 500;

    auto queue = this->clientTCP_.GetQueue();

    if (!queue.empty()) {
      message = queue.front();

      if (message.messageType == type) {
        success = (this->*handler)(message);
        queue.pop();
        break;
      }
    }
  }

  return success;
}

template <>
bool Client::WaitForMessage<NetworkProtocolType::kUDP>(
        MessageServerType type, bool (Client::*handler)(const tools::MessageProps &message)) {
  std::size_t timeout = kServerResponseTimeout;
  MessageProps message;
  bool success = false;

  if (!this->clientUDP_.has_value())
    return false;

  while (timeout > 0) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    timeout -= 500;

    auto queue = this->clientUDP_->GetQueue();

    if (!queue.empty()) {
      message = queue.front();

      if (message.messageType == type) {
        success = (this->*handler)(message);
        queue.pop();
        break;
      }
    }
  }

  return success;
}
