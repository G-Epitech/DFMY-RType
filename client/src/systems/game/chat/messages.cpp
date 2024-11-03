/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** player.cpp
*/

#include "messages.hpp"

#include <iostream>
#include <utility>

#include "client/src/constants/settings.hpp"
#include "constants/chat.hpp"
#include "libs/game/src/types/projectile.hpp"

using namespace rtype::client::systems;
using namespace rtype::client::services;
using namespace mew::sets::drawable;
using namespace core::components;

ChatMessagesSystem::ChatMessagesSystem(WindowManager::Ptr window_manager,
                                       ServerConnectionService::Ptr server_connection_service,
                                       const std::string& username, Registry::Ptr r)
    : ASystem(),
      windowManager_(std::move(window_manager)),
      serverConnectionService_{std::move(server_connection_service)} {
  const auto entity = r->SpawnEntity();
  const Vector3f point{CHAT_PIXELS_LEFT, windowManager_->height_ - 50, 0};
  constexpr Alignment rightAligns{HorizontalAlign::kRight, VerticalAlign::kCenter};
  const std::string final = username + " - ";

  r->AddComponent<Position>(entity, Position{point, rightAligns});
  r->AddComponent<Drawable>(entity,
                            {Text{final, "main", CHAT_CHAR_SIZE}, WindowManager::View::HUD});

  const auto entity2 = r->SpawnEntity();
  const Vector3f point2{CHAT_PIXELS_LEFT,
                        windowManager_->height_ - 50 + (static_cast<float>(CHAT_CHAR_SIZE) / 2) + 5,
                        0};
  constexpr Alignment leftAligns{HorizontalAlign::kLeft, VerticalAlign::kCenter};

  r->AddComponent<Position>(entity2, Position{point2, leftAligns});
  r->AddComponent<Drawable>(entity2,
                            {Rectangle{sf::Color::White, {300, 1}}, WindowManager::View::HUD});
}

void ChatMessagesSystem::Run(Registry::Ptr r) {
  const auto messages = serverConnectionService_->client()->ExtractChatQueue();

  for (const auto& message : messages) {
    MoveAllPositions(r);
    AddMessage(r, message);
    AddUsername(r, message);
  }
  CleanupOldMessages(r);
}

void ChatMessagesSystem::MoveAllPositions(Registry::Ptr r) {
  for (auto&& entity : oldMessages_) {
    auto&& position = r->GetComponent<Position>(entity.first);
    if (position) {
      auto&& pos = *position;
      pos->point.y -= 20;
    }
  }
}

void ChatMessagesSystem::AddMessage(const Registry::Ptr& r,
                                    const api::payload::ChatMessage& message) {
  const auto entity = r->SpawnEntity();
  const Vector3f point{CHAT_PIXELS_LEFT, windowManager_->height_ - 80, 0};
  constexpr Alignment aligns{HorizontalAlign::kLeft, VerticalAlign::kCenter};

  r->AddComponent<Position>(entity, Position{point, aligns});
  r->AddComponent<Drawable>(
      entity, {Text{message.message, "main", CHAT_CHAR_SIZE}, WindowManager::View::HUD});
  oldMessages_[entity] = std::chrono::system_clock::now();
}

void ChatMessagesSystem::AddUsername(const Registry::Ptr& r,
                                     const api::payload::ChatMessage& message) {
  const auto entity = r->SpawnEntity();
  const Vector3f point{CHAT_PIXELS_LEFT, windowManager_->height_ - 80, 0};
  constexpr Alignment aligns{HorizontalAlign::kRight, VerticalAlign::kCenter};
  const std::string name = message.username;
  const std::string finalMessage = name + " - ";

  r->AddComponent<Position>(entity, Position{point, aligns});
  r->AddComponent<Drawable>(entity,
                            {Text{finalMessage, "main", CHAT_CHAR_SIZE}, WindowManager::View::HUD});
  oldMessages_[entity] = std::chrono::system_clock::now();
}

void ChatMessagesSystem::CleanupOldMessages(Registry::Ptr r) {
  auto it = oldMessages_.begin();
  while (it != oldMessages_.end()) {
    std::chrono::time_point<std::chrono::system_clock> time = it->second;
    const auto&& now = std::chrono::system_clock::now();
    const auto&& diff = std::chrono::duration_cast<std::chrono::seconds>(now - time).count();
    if (diff >= CHAT_MESSAGE_SECONDS_LIFETIME) {
      r->KillEntity(it->first);
      it = oldMessages_.erase(it);
    } else {
      ++it;
    }
  }
}
