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
  const bool prevChatOpen = settingsManager_->Get<bool>(SETTING_GAME_CHAT_OPEN);
  bool chatOpen = prevChatOpen;

  for (auto&& [tags] : components) {
    if (tags & "chat") {
      for (const auto& event : events) {
        if (event.type == sf::Event::KeyPressed) {
          if (!prevChatOpen && IsChatOpenKey(event)) {
            OpenChat(tags);
            updated = true;
            chatOpen = true;
          } else if (prevChatOpen && IsChatCloseKey(event)) {
            CloseChat(tags);
            updated = true;
            chatOpen = false;
          }
        }
      }
    }
  }
  if (updated) {
    settingsManager_->Set(SETTING_GAME_CHAT_OPEN, chatOpen);
  }
}

bool ChatTriggerSystem::IsChatOpenKey(const sf::Event& event) {
  return event.key.code == sf::Keyboard::T;
}

bool ChatTriggerSystem::IsChatCloseKey(const sf::Event& event) {
  return event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter;
}

void ChatTriggerSystem::OpenChat(Tags& tags) {
  tags.RemoveTag("disabled");
}

void ChatTriggerSystem::CloseChat(Tags& tags) {
  tags.AddTag("disabled");
}
