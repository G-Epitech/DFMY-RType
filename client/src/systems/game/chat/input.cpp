/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** player.cpp
*/

#include "input.hpp"

#include <iostream>
#include <utility>

#include "client/src/constants/settings.hpp"
#include "libs/game/src/types/projectile.hpp"

using namespace rtype::client::systems;
using namespace rtype::client::services;

ChatInputSystem::ChatInputSystem(WindowManager::Ptr window_manager,
                                 ServerConnectionService::Ptr server_connection_service)
    : ASystem(),
      windowManager_(std::move(window_manager)),
      serverConnectionService_{std::move(server_connection_service)} {}

void ChatInputSystem::Run(Registry::Ptr r, zipper<Tags, Drawable> components) {
  const auto events = windowManager_->GetDeferredEvents();

  for (auto&& [tags, drawable] : components) {
    if (tags & "chat_input") {
      for (const auto& event : events) {
        if (event.type == sf::Event::KeyPressed) {
          auto&& component = std::get<Text>(drawable.drawable);
          if (event.key.code == sf::Keyboard::Enter) {
            if (!component.text.empty()) {
              auto res = serverConnectionService_->client()->SendMessage(component.text);
              if (!res) {
                std::cerr << "Failed to send message: '" << component.text << "'" << std::endl;
              } else {
                component.text = "";
              }
            }
          }
        }
      }
    }
  }
}
