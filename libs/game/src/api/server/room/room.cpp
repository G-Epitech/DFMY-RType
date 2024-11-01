/*
** EPITECH PROJECT, 2024
** room.cpp
** File description:
** Room class
*/

#include "room.hpp"

using namespace rtype::sdk::game::api;

Room::Room(std::size_t nodePort, const std::function<void(std::uint64_t)> &newPlayerHandler,
           std::uint64_t roomId)
    : nodeSocket_(kLocalhost, nodePort, [this](auto &msg) { return NodeMessageMiddleware(msg); }),
      chatSocket_(
          0, [this](auto &msg) { return ChatMessageMiddleware(msg); }, nullptr),
      logger_("Room"),
      roomId_(roomId) {
  this->newPlayerHandler_ = newPlayerHandler;

  InitNodeThread();
  InitClientsThread();
  InitChatThread();
}

Room::~Room() {
  this->nodeSocket_.Close();
  this->nodeThread_.join();

  logger_.Info("Node thread stopped", "🛑");

  this->clientsSocket_.Close();
  this->clientsThread_.join();

  logger_.Info("Clients thread stopped", "🛑");

  this->chatSocket_.Close();
  this->chatThread_.join();

  logger_.Info("Chat thread stopped", "🛑");
}

void Room::RegisterNewRoom() {
  payload::RegisterRoom payload = {
      .id = this->roomId_,
      .token = "token",
      .gamePort = this->clientsSocket_.GetEndpoint().port,
      .chatPort = static_cast<unsigned int>(this->chatSocket_.GetPort()),
  };

  this->SendToNode(RoomToNodeMsgType::kMsgTypeRTNRegisterRoom, payload);

  logger_.Info("Room registered", "🛂");
}

void Room::InitNodeThread() {
  this->nodeThread_ = std::thread(&abra::client::ClientTCP::Listen, &this->nodeSocket_);

  logger_.Info("Node TCP thread started", "🚀");
}

void Room::InitClientsThread() {
  this->clientsThread_ = std::thread(&abra::server::ServerUDP::Start, &this->clientsSocket_);

  logger_.Info("Clients UDP thread started", "🚀");
}

void Room::InitChatThread() {
  this->chatThread_ = std::thread(&abra::server::ServerTCP::Start, &this->chatSocket_);

  logger_.Info("Chat TCP thread started", "🚀");
}

std::queue<std::pair<std::uint64_t, abra::server::ClientUDPMessage>> Room::ExtractQueue() {
  auto queue = this->clientsSocket_.ExtractQueue();
  std::queue<std::pair<std::uint64_t, abra::server::ClientUDPMessage>> extractedQueue;

  while (!queue.empty()) {
    auto message = queue.front();
    auto userId = this->FindUserByEndpoint(message.endpoint);

    extractedQueue.emplace(userId, queue.front());
    queue.pop();
  }

  return extractedQueue;
}

std::uint64_t Room::FindUserByEndpoint(const boost::asio::ip::udp::endpoint &endpoint) {
  for (const auto &client : this->clients_) {
    if (client.endpoint == endpoint) {
      return client.id;
    }

    if (client.endpoint.address().to_string() == kLocalhost &&
        endpoint.address().to_string() == kIpNull) {
      return client.id;
    }

    if (client.endpoint.address().to_string() == kIpNull &&
        endpoint.address().to_string() == kLocalhost) {
      return client.id;
    }
  }

  return 0;
}

bool Room::SendPlayersState(const std::vector<payload::PlayerState> &state) {
  auto success = this->SendToClients(RoomToClientMsgType::kMsgTypeRTCPlayersState, state);
  if (success) {
    this->logger_.Info("Players state sent", "🦹");
  }

  return success;
}

bool Room::SendEnemiesState(const std::vector<payload::EnemyState> &state) {
  auto success = this->SendToClients(RoomToClientMsgType::kMsgTypeRTCEnemiesState, state);
  if (success) {
    this->logger_.Info("Enemies state sent", "🧌");
  }

  return success;
}

bool Room::SendBulletsState(const std::vector<payload::BulletState> &state) {
  auto success = this->SendToClients(RoomToClientMsgType::kMsgTypeRTCBulletsState, state);
  if (success) {
    this->logger_.Info("Bullets state sent", "💥");
  }

  return success;
}

bool Room::StartGame() {
  auto success = this->SendToNode(RoomToNodeMsgType::kMsgTypeRTNGameStarted, '\0');
  if (success) {
    this->logger_.Info("Game started", "🎮");
  }

  return success;
}

bool Room::EndGame(unsigned int score, time_t time, bool win) {
  payload::GameEnd end = {
      .score = score,
      .time = time,
      .win = win,
  };

  auto success = this->SendToNode(RoomToNodeMsgType::kMsgTypeRTNGameEnded, end);
  if (success) {
    this->logger_.Info("Game ended", "🏁");
  }

  return success;
}

bool Room::NodeMessageMiddleware(const abra::tools::MessageProps &message) {
  if (nodeMessageHandlers_.find(message.messageType) == nodeMessageHandlers_.end()) {
    return true;
  }

  logger_.Info("Handling message (node middleware catch)", "🔧");
  (this->*(nodeMessageHandlers_[message.messageType]))(message);

  return false;
}

bool Room::ChatMessageMiddleware(const abra::server::ClientTCPMessage &message) {
  if (chatMessageHandlers_.find(message.messageType) == chatMessageHandlers_.end()) {
    return true;
  }

  logger_.Info("Handling message (chat middleware catch)", "🔧");
  (this->*(chatMessageHandlers_[message.messageType]))(message);

  return false;
}

void Room::HandlePlayerJoin(const abra::tools::MessageProps &message) {
  try {
    auto packet = this->packetBuilder_.Build<payload::PlayerJoin>(message.data);
    auto &payload = packet->GetPayload();

    boost::asio::ip::udp::endpoint endpoint = {boost::asio::ip::address::from_string(payload.ip),
                                               kClientUDPPort};
    RoomClient newClient = {
        .id = payload.id,
        .username = payload.username,
        .endpoint = endpoint,
        .chatId = this->clients_.size(),
    };

    this->clients_.push_back(newClient);

    this->logger_.Info("Player joined", "👤");

    this->newPlayerHandler_(payload.id);
  } catch (std::exception &e) {
    this->logger_.Error("Failed to handle player join: " + std::string(e.what()), "❌");
  }
}

void Room::HandleNewMessage(const abra::server::ClientTCPMessage &message) {
  try {
    auto packet = this->packetBuilder_.Build<payload::SendMessage>(message.bitset);
    auto &payload = packet->GetPayload();

    this->logger_.Info("New message: " + std::string(payload.message), "💬");

    auto clientIt = std::find_if(
        this->clients_.begin(), this->clients_.end(),
        [&message](const RoomClient &client) { return client.chatId == message.clientId; });

    payload::ChatMessage chatPayload = {};
    snprintf(chatPayload.message, sizeof(chatPayload.message), "%s", payload.message);
    snprintf(chatPayload.username, sizeof(chatPayload.username), "%s", clientIt->username.c_str());

    this->SendToChats(RoomToClientMsgType::kMsgTypeRTCChatMessage, chatPayload);
  } catch (std::exception &e) {
    this->logger_.Error("Failed to handle new message: " + std::string(e.what()), "❌");
  }
}
