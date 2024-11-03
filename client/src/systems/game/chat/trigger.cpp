/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** trigger.cpp
*/

#include "trigger.hpp"

#include <iostream>
#include <utility>

#include "client/src/constants/settings.hpp"
#include "constants/chat.hpp"
#include "libs/game/src/types/projectile.hpp"

using namespace rtype::client::systems;
using namespace rtype::client::services;

ChatTriggerSystem::ChatTriggerSystem(WindowManager::Ptr window_manager,
                                     SettingsManager::Ptr settings_manager)
    : ASystem(),
      windowManager_(std::move(window_manager)),
      settingsManager_(std::move(settings_manager)) {}

void ChatTriggerSystem::Run(Registry::Ptr r, zipper<Tags> components) {
  const auto events = windowManager_->GetDeferredEvents();
  bool updated = false;
  const bool prevChatOpen = settingsManager_->Get<bool>(CHAT_IS_OPEN);
  bool chatOpen = prevChatOpen;

  for (auto&& [tags] : components) {
    if (tags & "chat") {
      for (const auto& event : events) {
        if (event.type == sf::Event::KeyPressed) {
          if (!prevChatOpen && IsChatOpenKey(event)) {
            tags.RemoveTag("disabled");
            updated = true;
            chatOpen = true;
          } else if (prevChatOpen && IsChatCloseKey(event)) {
            tags.AddTag("disabled");
            updated = true;
            chatOpen = false;
          }
        }
      }
    }
  }
  if (updated) {
    settingsManager_->Set(CHAT_IS_OPEN, chatOpen);
  }
}

bool ChatTriggerSystem::IsChatOpenKey(const sf::Event& event) {
  return event.key.code == sf::Keyboard::T;
}

bool ChatTriggerSystem::IsChatCloseKey(const sf::Event& event) {
  return event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter;
}
