/*
** EPITECH PROJECT, 2024
** client.cpp
** File description:
** Client class
*/

#include "./client.hpp"

using namespace rtype::sdk::game::api;
using namespace abra::client;
using namespace abra::tools;

Client::Client(const std::string &ip, const uint32_t &port)
    : clientTCP_(ip, port, nullptr),
      isConnected_(false),
      isLobbyConnected_(false),
      logger_("clientAPI") {
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

bool Client::Register(const payload::PlayerConnect &payload) {
  auto sendSuccess = SendPayloadTCP(ClientToMasterMsgType::kMsgTypeCTMConnect, payload);
  if (!sendSuccess)
    return false;

  logger_.Info("Register to server", "🛜");

  return this->isConnected_;
}

bool Client::HandleConnectionConfirmation(const MessageProps &) {
  this->isConnected_ = true;

  return true;
}

bool Client::JoinLobby(const payload::JoinRoom &payload) {
  auto sendSuccess = SendPayloadTCP(ClientToMasterMsgType::kMsgTypeCTMJoinRoom, payload);
  if (!sendSuccess)
    return false;

  auto waitSuccess =
      WaitForMessage(MasterToClientMsgType::kMsgTypeMTCInfoRoom, &Client::HandleJoinLobbyInfos);

  if (!waitSuccess) {
    logger_.Error("Connection to lobby failed", "💢️");
  } else {
    logger_.Info("Connected to lobby", "🛜");
  }

  return this->isLobbyConnected_;
}

bool Client::HandleJoinLobbyInfos(const MessageProps &message) {
  auto packet = this->packetBuilder_.Build<payload::InfoRoom>(message.data);
  auto payload = packet->GetPayload();

  logger_.Info("Joining lobby " + std::string(payload.ip) + ":" + std::to_string(payload.port),
               "🚪");

  this->clientUDP_.emplace(payload.ip, payload.port, kClientUDPPort);
  InitUDP();

  this->isLobbyConnected_ = true;
  return true;
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

  // logger_.Info("Extracted " + std::to_string(queue.size()) + " messages", "📬");

  return queue;
}

bool Client::Shoot(const payload::Shoot &payload) {
  auto success = SendPayloadUDP(ClientToRoomMsgType::kMsgTypeCTRPlayerShoot, payload);
  if (success) {
    logger_.Info("Player shoot with type " + std::to_string(static_cast<double>(payload.type)),
                 "🔫");
  }

  return success;
}

bool Client::Move(const payload::Movement &payload) {
  auto success = SendPayloadUDP(ClientToRoomMsgType::kMsgTypeCTRPlayerMove, payload);
  if (success) {
    logger_.Info("Player move", "🚶🏽");
  }

  return success;
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
  auto players =
      ResolvePayloads<payload::PlayerState>(RoomToClientMsgType::kMsgTypeRTCPlayersState, message);

  logger_.Info("Resolved " + std::to_string(players.size()) + " player states", "🦹");

  return players;
}

std::vector<payload::EnemyState> Client::ResolveEnemiesState(const Client::ServerMessage &message) {
  auto players =
      ResolvePayloads<payload::EnemyState>(RoomToClientMsgType::kMsgTypeRTCEnemiesState, message);

  logger_.Info("Resolved " + std::to_string(players.size()) + " enemies states", "🧌");

  return players;
}

std::vector<payload::BulletState> Client::ResolveBulletsState(
    const Client::ServerMessage &message) {
  auto players =
      ResolvePayloads<payload::BulletState>(RoomToClientMsgType::kMsgTypeRTCBulletsState, message);

  logger_.Info("Resolved " + std::to_string(players.size()) + " bullets states", "💥");

  return players;
}

bool api::Client::WaitForMessage(MasterToClientMsgType type,
                                 bool (Client::*handler)(const abt::MessageProps &message)) {
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
