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
    AddMesage(r, message);
  }
}

void ChatMessagesSystem::MoveAllPositions(Registry::Ptr r) {
  for (auto&& entity : oldMessages_) {
    auto&& position = r->GetComponent<Position>(entity);
    if (position) {
      auto&& pos = *position;
      pos->point.y -= 20;
    }
  }
}

void ChatMessagesSystem::AddMesage(const Registry::Ptr& r,
                                   const api::payload::ChatMessage& message) {
  const auto entity = r->SpawnEntity();
  const Vector3f point{10, windowManager_->height_ - 80, 0};
  constexpr Alignment aligns{HorizontalAlign::kLeft, VerticalAlign::kCenter};
  const std::string name = message.username;
  const std::string text = message.message;
  const std::string finalText = "[" + name + "] " + text;

  r->AddComponent<Position>(entity, Position{point, aligns});
  r->AddComponent<Drawable>(entity, {Text{finalText, "main"}, WindowManager::View::HUD});
  oldMessages_.push_back(entity);
}
