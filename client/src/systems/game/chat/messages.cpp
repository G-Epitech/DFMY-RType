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
#include "libs/game/src/types/projectile.hpp"

using namespace rtype::client::systems;
using namespace rtype::client::services;
using namespace mew::sets::drawable;
using namespace core::components;

ChatMessagesSystem::ChatMessagesSystem(WindowManager::Ptr window_manager,
                                       ServerConnectionService::Ptr server_connection_service)
    : ASystem(),
      windowManager_(std::move(window_manager)),
      serverConnectionService_{std::move(server_connection_service)} {}

void ChatMessagesSystem::Run(Registry::Ptr r) {
  const auto messages = serverConnectionService_->client()->ExtractChatQueue();

  for (const auto& message : messages) {
    MoveAllPositions(r);
    AddMessage(r, message);
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
  const Vector3f point{10, windowManager_->height_ - 80, 0};
  constexpr Alignment aligns{HorizontalAlign::kLeft, VerticalAlign::kCenter};
  const std::string name = message.username;
  const std::string text = message.message;
  const std::string finalText = "[" + name + "] " + text;

  r->AddComponent<Position>(entity, Position{point, aligns});
  r->AddComponent<Drawable>(entity, {Text{finalText, "main"}, WindowManager::View::HUD});
  oldMessages_[entity] = std::chrono::system_clock::now();
}

void ChatMessagesSystem::CleanupOldMessages(Registry::Ptr r) {
  for (auto&& entity : oldMessages_) {
    std::chrono::time_point<std::chrono::system_clock> time = entity.second;
    const auto&& now = std::chrono::system_clock::now();
    const auto&& diff = std::chrono::duration_cast<std::chrono::seconds>(now - time).count();
    if (diff >= CHAT_MESSAGE_SECONDS_LIFETIME) {
      r->KillEntity(entity.first);
      oldMessages_.erase(entity.first);
    }
  }
}
