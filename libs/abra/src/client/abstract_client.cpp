/*
** EPITECH PROJECT, 2024
** abstract_client.cpp
** File description:
** AbstractClient class
*/

#include "./abstract_client.hpp"

#include "libs/abra/src/tools/packet/packet_utils.hpp"

using namespace abra::client;

AbstractClient::AbstractClient(const std::string &name) : logger_(name) {
  this->middleware_ = nullptr;
}

void client::AbstractClient::ResolveBuffer(std::vector<char> *buffer, std::size_t len) {
  if (this->haveTemporaryBuffer) {
    buffer->insert(buffer->begin(), this->tempBuffer.begin(), this->tempBuffer.end());

    len += this->tempBuffer.size();

    this->haveTemporaryBuffer = false;
    this->tempBuffer.clear();
  }

  if (len < kPacketHeaderPropsSize / 8) {
    return;
  }

  auto bitset = std::make_shared<tools::dynamic_bitset>(*buffer, len);
  auto header = tools::PacketUtils::ExportHeaderFromBitset(bitset);
  std::size_t packetSize = (kPacketHeaderPropsSize + kPacketMessagePropsSize) / 8;

  if (header.offsetFlag) {
    packetSize += kPacketOffsetPropsSize / 8;
  }
  if (header.turnFlag) {
    packetSize += kPacketTurnPropsSize / 8;
  }
  packetSize += header.payloadLength;

  if (packetSize == len) {
    return StoreMessage(bitset, header.offsetFlag);
  }

  if (packetSize > len) {
    this->tempBuffer = *buffer;
    this->haveTemporaryBuffer = true;

    logger_.Info("Store temporary buffer with size " + std::to_string(len));
    return;
  }

  logger_.Info("Receive too bigger packet (" + std::to_string(len) + " bytes) than expected (" +
               std::to_string(packetSize) + " bytes)");

  std::vector<char> cleanBuffer(
      buffer->begin(),
      buffer->begin() + static_cast<std::vector<char>::difference_type>(packetSize));
  auto cleanBitset = std::make_shared<tools::dynamic_bitset>(cleanBuffer, packetSize);

  StoreMessage(cleanBitset, header.offsetFlag);

  buffer->erase(buffer->begin(),
                buffer->begin() + static_cast<std::vector<char>::difference_type>(packetSize));
  return ResolveBuffer(buffer, len - packetSize);
}

void AbstractClient::HandleMultiPacketsBitset(std::shared_ptr<tools::dynamic_bitset> bitset) {
  auto messageId = tools::PacketUtils::ExportMessageIdFromBitset(bitset);
  auto offset = tools::PacketUtils::ExportOffsetFromBitset(bitset);
  auto messageType = tools::PacketUtils::ExportMessageTypeFromBitset(bitset);

  if (pendingMultiPackets_.find(messageId) == pendingMultiPackets_.end()) {
    pendingMultiPackets_[messageId] = tools::MultipleMessagesProps();
  } else {
    if (pendingMultiPackets_[messageId].messages.empty() ||
        pendingMultiPackets_[messageId].messages[0].messageType != messageType) {
      pendingMultiPackets_[messageId] = tools::MultipleMessagesProps();
    }
  }

  tools::MultipleMessageProps message = {
      .messageId = messageId,
      .messageType = messageType,
      .offset = offset.offset,
      .isLast = offset.offsetFlag == 1,
      .data = std::move(bitset),
  };

  pendingMultiPackets_[messageId].messages.push_back(std::move(message));

  auto &lastMessage = pendingMultiPackets_[messageId].messages.back();
  if (lastMessage.isLast) {
    pendingMultiPackets_[messageId].lastMessage = &lastMessage;

    logger_.Info("Store last part of multi packet with type " +
                 std::to_string(message.messageType) + " and offset " +
                 std::to_string(offset.offset));
  }

  logger_.Info("Store a part of multi packet with type " + std::to_string(message.messageType) +
               " and offset " + std::to_string(offset.offset));

  ResolveMultiPackets(messageId);
}

void AbstractClient::StoreMessage(std::shared_ptr<tools::dynamic_bitset> bitset, bool hasOffset) {
  if (hasOffset) {
    HandleMultiPacketsBitset(bitset);
  } else {
    tools::MessageProps message = {tools::PacketUtils::ExportMessageIdFromBitset(bitset),
                                   tools::PacketUtils::ExportMessageTypeFromBitset(bitset), bitset};
    logger_.Info("Store message with type " + std::to_string(message.messageType));

    if (this->middleware_ == nullptr || this->middleware_(message)) {
      std::unique_lock<std::mutex> lock(this->Mutex);
      this->queue_.push(message);
    }
  }
}

void AbstractClient::ResolveMultiPackets(unsigned int messageId) {
  if (pendingMultiPackets_[messageId].lastMessage != nullptr &&
      pendingMultiPackets_[messageId].messages.size() ==
          pendingMultiPackets_[messageId].lastMessage->offset + 1) {
    this->multiPackets_.push(std::move(pendingMultiPackets_[messageId].messages));
    pendingMultiPackets_.erase(messageId);

    logger_.Info("Resolve multi packet with id " + std::to_string(messageId));
  }
}

std::queue<tools::MessageProps> AbstractClient::ExtractQueue() {
  std::unique_lock<std::mutex> lock(this->Mutex);

  auto queue = this->queue_;
  this->queue_ = std::queue<tools::MessageProps>();

  return queue;
}

std::queue<std::vector<tools::MultipleMessageProps>> AbstractClient::ExtractMultiQueue() {
  std::unique_lock<std::mutex> lock(this->Mutex);

  auto queue = this->multiPackets_;
  this->multiPackets_ = std::queue<std::vector<tools::MultipleMessageProps>>();

  return queue;
}
