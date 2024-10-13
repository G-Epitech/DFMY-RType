/*
** EPITECH PROJECT, 2024
** client.cpp
** File description:
** Client class
*/

#include "client.hpp"

using namespace rtype::sdk::game::api;
using namespace abra::client;
using namespace abra::tools;

Client::Client(const std::string &ip, const uint32_t &port)
    : clientTCP_(ip, port), isConnected_(false), isLobbyConnected_(false), logger_("clientAPI") {
  InitTCP();
}

Client::~Client() {
  this->clientTCP_.Close();
  this->threadTCP_.join();

  logger_.Info("Client TCP thread stopped", "🛑");

  if (this->isLobbyConnected_) {
    this->clientUDP_->Close();
    this->threadUDP_.join();

    logger_.Info("Client UDP thread stopped", "🛑");
  }
}

void Client::InitTCP() {
  this->threadTCP_ = std::thread(&Client::ListenTCP, this);
  logger_.Info("Client TCP thread started", "🚀");
}

void Client::ListenTCP() {
  this->clientTCP_.Listen();
}

void Client::InitUDP() {
  this->threadUDP_ = std::thread(&Client::ListenUDP, this);
  logger_.Info("Client UDP thread started", "🚀");
}

void Client::ListenUDP() {
  this->clientUDP_->Listen();
}

bool Client::IsConnected() const {
  return this->isConnected_;
}

bool Client::Register(const payload::Connection &payload) {
  auto sendSuccess = SendPayloadTCP(MessageClientType::kConnection, payload);
  if (!sendSuccess)
    return false;

  auto waitSuccess = WaitForMessage<NetworkProtocolType::kTCP>(
      MessageServerType::kConnectionInfos, &Client::HandleConnectionConfirmation);

  if (!waitSuccess) {
    logger_.Error("Register failed", "💢️");
  }

  logger_.Info("Register to server", "🛜");

  return this->isConnected_;
}

bool Client::HandleConnectionConfirmation(const MessageProps &) {
  this->isConnected_ = true;

  return true;
}

bool Client::JoinLobby(const payload::JoinLobby &payload) {
  auto sendSuccess = SendPayloadTCP(MessageClientType::kJoinLobby, payload);
  if (!sendSuccess)
    return false;

  auto waitSuccess = WaitForMessage<NetworkProtocolType::kTCP>(
      MessageServerType::kServerJoinLobbyInfos, &Client::HandleJoinLobbyInfos);

  if (!waitSuccess) {
    logger_.Error("Connection to lobby failed", "💢️");
  } else {
    logger_.Info("Connected to lobby", "🛜");
  }

  return this->isLobbyConnected_;
}

bool Client::HandleJoinLobbyInfos(const MessageProps &message) {
  auto packet = this->packetBuilder_.Build<payload::JoinLobbyInfos>(message.data);
  auto payload = packet->GetPayload();

  logger_.Info("Joining lobby " + std::string(payload.ip) + ":" + std::to_string(payload.port),
               "🚪");

  this->clientUDP_.emplace("127.0.0.1", payload.port);
  InitUDP();

  auto endpoint = this->clientUDP_->GetEndpoint();
  payload::JoinLobbyInfos infoPayload{};

  const char *ipPtr = endpoint.ip.c_str();
  strncpy(infoPayload.ip, ipPtr, 16);
  infoPayload.port = endpoint.port;

  auto success = SendPayloadTCP(MessageClientType::kClientJoinLobbyInfos, infoPayload);
  if (!success) {
    logger_.Error("Joining lobby failed", "💢️");
  }

  this->isLobbyConnected_ = success;
  return success;
}

std::queue<Client::ServerMessage> Client::ExtractQueue() {
  auto queue = std::queue<ServerMessage>();

  auto queueTCP = this->clientTCP_.ExtractQueue();
  Client::ConvertQueueData(&queueTCP, &queue);

  if (!this->isLobbyConnected_) {
    logger_.Info("Extracted " + std::to_string(queue.size()) + " messages", "📬");
    return queue;
  }

  auto queueUDP = this->clientUDP_->ExtractQueue();
  Client::ConvertQueueData(&queueUDP, &queue);

  auto multiQueue = this->clientUDP_->ExtractMultiQueue();
  while (!multiQueue.empty()) {
    auto &multiMessages = multiQueue.front();

    std::vector<std::shared_ptr<abra::tools::dynamic_bitset>> data;
    data.reserve(multiMessages.messages.size());

    for (auto &message : multiMessages.messages) {
      data.push_back(message.data);
    }

    queue.push({.messageId = multiMessages.messages[0].messageId,
                .messageType = multiMessages.messages[0].messageType,
                .data = data});
    multiQueue.pop();
  }

  logger_.Info("Extracted " + std::to_string(queue.size()) + " messages", "📬");

  return queue;
}

bool Client::Shoot(const payload::Shoot &payload) {
  return SendPayloadUDP(MessageClientType::kShoot, payload);
}

bool Client::Move(const payload::Movement &payload) {
  return SendPayloadUDP(MessageClientType::kMovement, payload);
}

void Client::ConvertQueueData(std::queue<tools::MessageProps> *queue,
                              std::queue<ServerMessage> *serverQueue) {
  while (!queue->empty()) {
    auto &message = queue->front();

    serverQueue->push(
        {.messageId = message.messageId,
         .messageType = message.messageType,
         .data = std::vector<std::shared_ptr<abra::tools::dynamic_bitset>>{message.data}});
    queue->pop();
  }
}

std::vector<payload::PlayerState> Client::ResolvePlayersState(
    const Client::ServerMessage &message) {
  auto players = ResolvePayloads<payload::PlayerState>(MessageServerType::kPlayersState, message);

  logger_.Info("Resolved " + std::to_string(players.size()) + " player states", "🦹🏽");

  return players;
}

std::vector<payload::EnemyState> Client::ResolveEnemiesState(const Client::ServerMessage &message) {
  auto players = ResolvePayloads<payload::EnemyState>(MessageServerType::kEnemiesState, message);

  logger_.Info("Resolved " + std::to_string(players.size()) + " enemies states", "🧌");

  return players;
}

std::vector<payload::BulletState> Client::ResolveBulletsState(
    const Client::ServerMessage &message) {
  auto players = ResolvePayloads<payload::BulletState>(MessageServerType::kBulletsState, message);

  logger_.Info("Resolved " + std::to_string(players.size()) + " bullets states", "💥");

  return players;
}
