/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** player.cpp
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
  for (auto&& [tags] : components) {
    if (tags & "chat") {
      for (const auto& event : events) {
        if (event.type == sf::Event::KeyPressed) {
          if (!settingsManager_->Get<bool>(SETTING_GAME_CHAT_OPEN)) {
            if (event.key.code == sf::Keyboard::T) {
              settingsManager_->Set(SETTING_GAME_CHAT_OPEN, true);
            }
          } else {
            if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter) {
              settingsManager_->Set(SETTING_GAME_CHAT_OPEN, false);
            }
          }
        }
      }
    }
  }
}
