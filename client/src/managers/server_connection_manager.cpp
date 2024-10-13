/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** window_manager.cpp
*/

#include "server_connection_manager.hpp"

using namespace rtype::client;

ServerConnectionManager::ServerConnectionManager(ServerConnectionManager::Properties&& props)
    : props_(std::move(props)) {}

ServerConnectionManager::~ServerConnectionManager() {
  connectionStatus_ = ConnectionStatus::kDisconnected;
  if (connectionThread_.joinable())
    connectionThread_.join();
}

ServerConnectionManager::Ptr ServerConnectionManager::Create(
    ServerConnectionManager::Properties&& props) {
  return std::make_shared<ServerConnectionManager>(std::move(props));
}

bool ServerConnectionManager::Connected() const {
  return client_ != nullptr && connectionStatus_ == ConnectionStatus::kConnected;
}

void ServerConnectionManager::ConnectAsync() {
  if (connectionStatus_ == ConnectionStatus::kConnecting)
    return;
  connectionStatus_ = ConnectionStatus::kConnecting;
  nextRetry_ = std::chrono::system_clock::now();
  connectionThread_ = std::thread(&ServerConnectionManager::Connect, this);
}

void ServerConnectionManager::Connect() {
  while (connectionStatus_ == ConnectionStatus::kConnecting) {
    if (std::chrono::system_clock::now() < nextRetry_)
      continue;
    try {
      auto client = std::make_shared<api::Client>(props_.ip, props_.port);
      clientMutex_.lock();
      client_ = client;
      clientMutex_.unlock();
      connectionStatus_ = ConnectionStatus::kConnected;
    } catch (const std::exception& e) {
      std::cerr << "[ERROR]: Failed to connect to server: " << e.what() << std::endl;
      nextRetry_ = std::chrono::system_clock::now() + std::chrono::seconds(3);
    }
  }
}
