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

void ChatMessagesSystem::AddMesage(Registry::Ptr r, api::payload::ChatMessage message) {
  auto entity = r->SpawnEntity();
  const Vector3f point{windowManager_->width_ - 100, windowManager_->height_ - 120, 0};
  constexpr Alignment aligns{HorizontalAlign::kCenter, VerticalAlign::kCenter};

  r->AddComponent<Position>(entity, Position{point, aligns});
  r->AddComponent<Drawable>(entity, {Text{message.message, "main"}, WindowManager::View::HUD});
  oldMessages_.push_back(entity);
}
