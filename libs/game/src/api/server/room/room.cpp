/*
** EPITECH PROJECT, 2024
** room.cpp
** File description:
** Room class
*/

#include "room.hpp"

using namespace rtype::sdk::game::api;

Room::Room(const std::string &nodeIp, std::size_t nodePort,
           const std::function<void(std::uint64_t)> &newPlayerHandler, std::uint64_t roomId)
        : nodeSocket_(nodeIp, nodePort, [this](auto &msg) { return NodeMessageMiddleware(msg); }),
          logger_("Room"),
          roomId_(roomId) {
  this->newPlayerHandler_ = newPlayerHandler;

  InitNodeThread();
  InitClientsThread();
}

Room::~Room() {
  this->nodeSocket_.Close();
  this->nodeThread_.join();

  logger_.Info("Node thread stopped", "🛑");

  this->clientsSocket_.Close();
  this->clientsThread_.join();

  logger_.Info("Clients thread stopped", "🛑");
}

void Room::InitNodeThread() {
  this->nodeThread_ = std::thread(&abra::client::ClientTCP::Listen, &this->nodeSocket_);

  logger_.Info("Node TCP thread started", "🚀");
}

void Room::InitClientsThread() {
  this->clientsThread_ = std::thread(&abra::server::ServerUDP::Start, &this->clientsSocket_);

  logger_.Info("Clients UDP thread started", "🚀");
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
  for (const auto &client: this->clients_) {
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
  payload::RoomGameEnd end = {
          .id = this->roomId_,
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

void Room::HandlePlayerJoin(const abra::tools::MessageProps &message) {
  auto packet = this->packetBuilder_.Build<payload::PlayerJoin>(message.data);
  auto &payload = packet->GetPayload();

  boost::asio::ip::udp::endpoint endpoint = {boost::asio::ip::address::from_string(payload.ip), kClientUDPPort};
  RoomClient newClient = {
          .id = payload.id,
          .endpoint = endpoint,
  };

  this->clients_.push_back(newClient);

  this->newPlayerHandler_(payload.id);
}
