/*
** EPITECH PROJECT, 2024
** client.tpp
** File description:
** client class
*/

#pragma once

namespace api = rtype::sdk::game::api;
namespace abt = abra::tools;

template <typename T>
bool api::Client::SendPayloadTCP(const MessageClientType &type, const T &payload) {
  this->packetBuilder_.SetMessageType(type).SetPayloadType(abt::PayloadType::kCustom);
  auto packet = this->packetBuilder_.Build(payload);

  logger_.Info("Send packet (TCP) of type " + std::to_string(type), "📦");

  auto success = this->clientTCP_.Send(packet) == abt::SendMessageStatus::kSuccess;
  if (!success)
    logger_.Warning("Failed to send packet of type " + std::to_string(type), "⚠️ ");

  return success;
}

template <typename T>
bool api::Client::SendPayloadUDP(const MessageClientType &type, const T &payload) {
  if (!this->clientUDP_.has_value())
    return false;

  this->packetBuilder_.SetMessageType(type).SetPayloadType(abt::PayloadType::kCustom);
  auto packet = this->packetBuilder_.Build(payload);

  logger_.Info("Send packet (UDP) of type " + std::to_string(type), "📦");

  auto success = this->clientUDP_->Send(packet) == abt::SendMessageStatus::kSuccess;
  if (!success)
    logger_.Warning("Failed to send packet of type " + std::to_string(type), "⚠️ ");

  return success;
}

template <typename T>
std::vector<T> api::Client::ResolvePayloads(MessageLobbyType type, const ServerMessage &message) {
  if (message.messageType != type) {
    return {};
  }
  auto elements = std::vector<T>();

  for (auto &data : message.data) {
    auto packet = this->packetBuilder_.Build<T>(data);
    elements.push_back(packet->GetPayload());
  }

  return elements;
}

template <>
inline bool api::Client::WaitForMessage<api::NetworkProtocolType::kTCP>(
    MessageServerType type, bool (Client::*handler)(const abt::MessageProps &message)) {
  std::size_t timeout = kServerResponseTimeout;
  abt::MessageProps message;
  bool success = false;

  logger_.Info("Waiting for message type " + std::to_string(type), "😴");
  while (timeout > 0) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    timeout -= 500;

    auto &queue = this->clientTCP_.GetQueue();

    std::unique_lock<std::mutex> lock(this->clientTCP_.Mutex);
    if (!queue.empty()) {
      message = queue.front();

      if (message.messageType == type) {
        success = (this->*handler)(message);
        queue.pop();
        break;
      } else {
        logger_.Warning("Receive an other message of type " + std::to_string(message.messageType),
                        "⚠️ ");
      }
    }
  }

  return success;
}

template <>
inline bool api::Client::WaitForMessage<api::NetworkProtocolType::kUDP>(
    MessageServerType type, bool (Client::*handler)(const abt::MessageProps &message)) {
  std::size_t timeout = kServerResponseTimeout;
  abt::MessageProps message;
  bool success = false;

  if (!this->clientUDP_.has_value())
    return false;

  while (timeout > 0) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    timeout -= 500;

    auto queue = this->clientUDP_->GetQueue();

    std::unique_lock<std::mutex> lock(this->clientUDP_->Mutex);
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
