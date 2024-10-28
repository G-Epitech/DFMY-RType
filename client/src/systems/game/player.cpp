/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** player.cpp
*/

#include "player.hpp"

#include <iostream>
#include <utility>

#include "client/src/constants/settings.hpp"
#include "libs/game/src/types/projectile.hpp"

using namespace rtype::client::systems;
using namespace rtype::client::services;

PlayerSystem::PlayerSystem(SettingsManager::Ptr settings_manager, WindowManager::Ptr window_manager,
                           ServerConnectionService::Ptr server_connection_service)
    : ASystem(),
      settingsManager_{std::move(settings_manager)},
      windowManager_{std::move(window_manager)},
      serverConnectionService_{std::move(server_connection_service)} {}

void PlayerSystem::Run(Registry::Ptr r) {
  const auto events = windowManager_->GetDeferredEvents();
  const auto key_map = settingsManager_->Get<KeyMap>(SETTING_GAME_KEYMAP);

  // If a key is pressed, we send a message to the server
  for (const auto &event : events) {
    const auto action_keyboard = key_map.GetActionFromKey(event.key.code);
    const auto action_mouse = key_map.GetActionFromMouse(event.mouseButton.button);

    if (event.type == sf::Event::KeyPressed) {
      UpdatePlayerActions(action_keyboard, true);
    } else if (event.type == sf::Event::KeyReleased) {
      UpdatePlayerActions(action_keyboard, false);
    } else if (event.type == sf::Event::MouseButtonPressed) {
      UpdatePlayerActions(action_mouse, true);
    } else if (event.type == sf::Event::MouseButtonReleased) {
      UpdatePlayerActions(action_mouse, false);
    }
  }
  ProcessPlayerActions();
}

void PlayerSystem::UpdatePlayerActions(const GameAction &action, const bool &isPressed) {
  switch (action) {
    case GameAction::kActionUp:
      isMovingUp_ = isPressed;
      break;
    case GameAction::kActionDown:
      isMovingDown_ = isPressed;
      break;
    case GameAction::kActionLeft:
      isMovingLeft_ = isPressed;
      break;
    case GameAction::kActionRight:
      isMovingRight_ = isPressed;
      break;
    case GameAction::kActionShoot:
      isShooting_ = isPressed;
      break;
    default:
      break;
  }
}

void PlayerSystem::ProcessPlayerActions() {
  if (isMovingUp_) {
    ProcessPlayerMoveUp();
  }
  if (isMovingDown_) {
    ProcessPlayerMoveDown();
  }
  if (isMovingLeft_) {
    ProcessPlayerMoveLeft();
  }
  if (isMovingRight_) {
    ProcessPlayerMoveRight();
  }
  if (isShooting_) {
    ProcessPlayerShoot();
  }
}

void PlayerSystem::ProcessPlayerMoveUp() {
  auto res = serverConnectionService_->client()->Move({
      .direction = {0, -1},
  });
  if (!res) {
    std::cerr << "Failed to move up" << std::endl;
  }
}

void PlayerSystem::ProcessPlayerMoveDown() {
  auto res = serverConnectionService_->client()->Move({
      .direction = {0, 1},
  });
  if (!res) {
    std::cerr << "Failed to move down" << std::endl;
  }
}

void PlayerSystem::ProcessPlayerMoveLeft() {
  auto res = serverConnectionService_->client()->Move({
      .direction = {-1, 0},
  });
  if (!res) {
    std::cerr << "Failed to move left" << std::endl;
  }
}

void PlayerSystem::ProcessPlayerMoveRight() {
  auto res = serverConnectionService_->client()->Move({
      .direction = {1, 0},
  });
  if (!res) {
    std::cerr << "Failed to move right" << std::endl;
  }
}

void PlayerSystem::ProcessPlayerShoot() {
  auto res = serverConnectionService_->client()->Shoot({
      .type = sdk::game::types::ProjectileType::kPlayerCommon,
  });
  if (!res) {
    std::cerr << "Failed to shoot" << std::endl;
  }
}
