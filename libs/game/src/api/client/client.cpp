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

    this->chatTCP_->Close();
    this->threadChatTCP_.join();

    logger_.Info("Client Chat TCP thread stopped", "🛑");
  }
}

void Client::InitTCP() {
  this->threadTCP_ = std::thread(&Client::ListenTCP, this);
  logger_.Info("Client TCP thread started", "🚀");
}

void Client::ListenTCP() {
  this->clientTCP_.Listen();
}

void Client::InitUDP(std::string ip, unsigned int port, unsigned int localPort) {
  this->clientUDP_.emplace(ip, port, localPort);

  this->threadUDP_ = std::thread(&Client::ListenUDP, this);
  logger_.Info("Client UDP thread started", "🚀");
}

void Client::ListenUDP() {
  this->clientUDP_->Listen();
}

void Client::InitChatTCP(std::string ip, unsigned int port) {
  this->chatTCP_.emplace(ip, port, nullptr);

  this->threadChatTCP_ = std::thread(&Client::ListenChatTCP, this);
  logger_.Info("Client Chat TCP thread started", "🚀");
}

void Client::ListenChatTCP() {
  this->chatTCP_->Listen();
}

bool Client::IsConnected() const {
  return this->isConnected_;
}

bool Client::Register(const payload::PlayerConnect &payload) {
  auto sendSuccess = SendPayloadTCP(ClientToMasterMsgType::kMsgTypeCTMConnect, payload);
  if (!sendSuccess)
    return false;

  this->isConnected_ = sendSuccess;
  logger_.Info("Register to server", "🛜");

  return this->isConnected_;
}

bool Client::HandleConnectionConfirmation(const MessageProps &) {
  this->isConnected_ = true;

  return true;
}

bool Client::JoinRoom(const payload::JoinRoom &payload) {
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

bool Client::CreateRoom(const payload::CreateRoom &payload) {
  auto success = SendPayloadTCP(ClientToMasterMsgType::kMsgTypeCTMCreateRoom, payload);
  if (success) {
    logger_.Info("Room created", "🏠");
  }

  return success;
}

bool Client::HandleJoinLobbyInfos(const MessageProps &message) {
  try {
    auto packet = this->packetBuilder_.Build<payload::InfoRoom>(message.data);
    auto payload = packet->GetPayload();

    InitUDP(payload.ip, payload.gamePort, kClientUDPPort);
    InitChatTCP(payload.ip, payload.chatPort);

    this->isLobbyConnected_ = SendMessage("> Join the room");

    logger_.Info(
        "Joining lobby " + std::string(payload.ip) + ":" + std::to_string(payload.gamePort), "🚪");
    return this->isLobbyConnected_;
  } catch (const std::exception &e) {
    logger_.Error("Failed to join lobby: " + std::string(e.what()), "❌");
    return false;
  }
}

std::queue<Client::ServerMessage> Client::ExtractQueue() {
  auto queue = std::queue<ServerMessage>();

  auto queueTCP = this->clientTCP_.ExtractQueue();
  Client::ConvertQueueData(&queueTCP, &queue, NetworkProtocolType::kTCP);

  if (!this->isLobbyConnected_) {
    return queue;
  }

  auto queueUDP = this->clientUDP_->ExtractQueue();
  Client::ConvertQueueData(&queueUDP, &queue, NetworkProtocolType::kUDP);

  auto multiQueue = this->clientUDP_->ExtractMultiQueue();
  while (!multiQueue.empty()) {
    auto &multiMessages = multiQueue.front();

    std::vector<std::shared_ptr<abra::tools::dynamic_bitset>> data;
    data.reserve(multiMessages.size());

    for (auto &message : multiMessages) {
      data.push_back(message.data);
    }

    queue.push({.messageId = multiMessages[0].messageId,
                .messageType = multiMessages[0].messageType,
                .protocolType = NetworkProtocolType::kUDP,
                .data = data});
    multiQueue.pop();
  }

  return queue;
}

std::vector<payload::ChatMessage> Client::ExtractChatQueue() {
  auto queue = this->chatTCP_->ExtractQueue();
  auto vector = std::vector<payload::ChatMessage>();

  while (!queue.empty()) {
    auto &message = queue.front();
    if (message.messageType != RoomToClientMsgType::kMsgTypeRTCChatMessage) {
      queue.pop();
      continue;
    }

    auto packet = this->packetBuilder_.Build<payload::ChatMessage>(message.data);
    auto payload = packet->GetPayload();

    vector.push_back(payload);
    queue.pop();
  }

  return vector;
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

bool Client::SendMessage(const std::string &message) {
  payload::SendMessage payload = {};

  snprintf(payload.message, sizeof(payload.message), "%s", message.c_str());

  auto success = SendChatPayloadTPC(ClientToRoomMsgType::kMsgTypeCTRSendMessage, payload);
  if (success) {
    logger_.Info("Send message", "💬");
  }

  return success;
}

void Client::ConvertQueueData(std::queue<tools::MessageProps> *queue,
                              std::queue<ServerMessage> *serverQueue,
                              NetworkProtocolType protocolType) {
  while (!queue->empty()) {
    auto &message = queue->front();

    serverQueue->push(
        {.messageId = message.messageId,
         .messageType = message.messageType,
         .protocolType = protocolType,
         .data = std::vector<std::shared_ptr<abra::tools::dynamic_bitset>>{message.data}});
    queue->pop();
  }
}

std::vector<payload::PlayerState> Client::ResolvePlayersState(
    const Client::ServerMessage &message) {
  auto players = ResolveUDPPayloads<payload::PlayerState>(
      RoomToClientMsgType::kMsgTypeRTCPlayersState, message);

  logger_.Info("Resolved " + std::to_string(players.size()) + " player states", "🦹");

  return players;
}

std::vector<payload::EnemyState> Client::ResolveEnemiesState(const Client::ServerMessage &message) {
  auto players = ResolveUDPPayloads<payload::EnemyState>(
      RoomToClientMsgType::kMsgTypeRTCEnemiesState, message);

  logger_.Info("Resolved " + std::to_string(players.size()) + " enemies states", "🧌");

  return players;
}

std::vector<payload::BulletState> Client::ResolveBulletsState(
    const Client::ServerMessage &message) {
  auto players = ResolveUDPPayloads<payload::BulletState>(
      RoomToClientMsgType::kMsgTypeRTCBulletsState, message);

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
        queue.pop();
      }
    }
  }

  return success;
}

bool Client::RefreshInfos(bool game, bool rooms) {
  payload::RefreshInfos payload = {.infoGame = game, .infoRooms = rooms};

  auto success = SendPayloadTCP(ClientToMasterMsgType::kMsgTypeCTMRefreshInfos, payload);
  if (success) {
    logger_.Info("Refresh infos", "🔄");
  }

  return success;
}

payload::InfoGame Client::ResolveGameInfo(const Client::ServerMessage &message) {
  auto payload =
      ResolveTCPPayloads<payload::InfoGame>(MasterToClientMsgType::kMsgTypeMTCInfoGame, message);

  logger_.Info("Resolved game infos", "🎮");

  return payload[0];
}

payload::InfoRooms Client::ResolveInfoRooms(const Client::ServerMessage &message) {
  auto payload =
      ResolveTCPPayloads<payload::InfoRooms>(MasterToClientMsgType::kMsgTypeMTCInfoRooms, message);

  logger_.Info("Resolved rooms infos", "🏠");

  return payload[0];
}

payload::GameEnd Client::ResolveRoomGameEnd(const Client::ServerMessage &message) {
  auto payload =
      ResolveTCPPayloads<payload::GameEnd>(MasterToClientMsgType::kMsgTypeMTCGameEnded, message);

  logger_.Info("Resolved room game end", "🏁");

  return payload[0];
}
