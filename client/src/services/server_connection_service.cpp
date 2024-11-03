/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** window_manager.cpp
*/

#include "server_connection_service.hpp"

#include "constants/settings.hpp"
#include "constants/user.hpp"

using namespace rtype::client::services;

ServerConnectionService::ServerConnectionService(const std::string& ip, std::uint32_t port)
    : props_{ip, port} {}

ServerConnectionService::~ServerConnectionService() {
  connectionStatus_ = ConnectionStatus::kDisconnected;
  if (connectionThread_ && connectionThread_->joinable()) {
    connectionThread_->join();
  }
}

bool ServerConnectionService::Connected() const {
  return client_ != nullptr && connectionStatus_ == ConnectionStatus::kConnected;
}

void ServerConnectionService::ConnectAsync(const std::string& username) {
  if (connectionThread_)
    return;
  connectionStatus_ = ConnectionStatus::kConnecting;
  nextRetry_ = std::chrono::system_clock::now() + std::chrono::seconds(1);
  connectionThread_ = std::thread(&ServerConnectionService::Connect, this, username);
}

void ServerConnectionService::Connect(const std::string& username) {
  char usernameChar[20] = {0};
  strncpy(usernameChar, username.c_str(), sizeof(usernameChar) - 1);

  while (connectionStatus_ != ConnectionStatus::kConnected) {
    if (std::chrono::system_clock::now() < nextRetry_)
      continue;
    try {
      auto client = std::make_shared<api::Client>(props_.ip, props_.port);
      clientMutex_.lock();
      client_ = client;
      clientMutex_.unlock();

      api::payload::PlayerConnect playerConnect{};
      std::memcpy(playerConnect.username, usernameChar, sizeof(playerConnect.username));

      auto res = client->Register(playerConnect);
      if (!res) {
        throw std::runtime_error("Failed to register to server");
      }
      connectionStatus_ = ConnectionStatus::kConnected;
    } catch (const std::exception& e) {
      connectionStatus_ = ConnectionStatus::kFailed;
      std::cerr << "[ERROR]: Failed to connect to server: " << e.what() << std::endl;
      nextRetry_ = std::chrono::system_clock::now() + std::chrono::seconds(3);
    }
  }
}

ServerConnectionService::ConnectionStatus ServerConnectionService::connectionStatus() const {
  return connectionStatus_;
}
