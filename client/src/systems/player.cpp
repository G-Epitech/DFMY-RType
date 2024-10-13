/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** player.cpp
*/

#include "player.hpp"

#include <iostream>

#include "libs/game/src/types/projectile.hpp"

using namespace rtype::client::systems;

PlayerSystem::PlayerSystem(const GlobalContext &context) : context_{context}, ASystem() {}

void PlayerSystem::Run(Registry::Ptr r) {
  const auto events = context_.windowManager->GetDeferredEvents();

  // If a key is pressed, we send a message to the server
  for (const auto &event : events) {
    const auto actionKeyBoard = context_.gameManager->keyMap.GetActionFromKey(event.key.code);
    const auto actionMouse =
        context_.gameManager->keyMap.GetActionFromMouse(event.mouseButton.button);
    if (event.type == sf::Event::KeyPressed) {
      UpdatePlayerActions(actionKeyBoard, true);
    } else if (event.type == sf::Event::KeyReleased) {
      UpdatePlayerActions(actionKeyBoard, false);
    } else if (event.type == sf::Event::MouseButtonPressed) {
      UpdatePlayerActions(actionMouse, true);
    } else if (event.type == sf::Event::MouseButtonReleased) {
      UpdatePlayerActions(actionMouse, false);
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
  auto res = context_.serverConnectionManager->client()->Move({
      .direction = {0, -1},
  });
  if (!res) {
    std::cerr << "Failed to move up" << std::endl;
  }
}

void PlayerSystem::ProcessPlayerMoveDown() {
  auto res = context_.serverConnectionManager->client()->Move({
      .direction = {0, 1},
  });
  if (!res) {
    std::cerr << "Failed to move down" << std::endl;
  }
}

void PlayerSystem::ProcessPlayerMoveLeft() {
  auto res = context_.serverConnectionManager->client()->Move({
      .direction = {-1, 0},
  });
  if (!res) {
    std::cerr << "Failed to move left" << std::endl;
  }
}

void PlayerSystem::ProcessPlayerMoveRight() {
  auto res = context_.serverConnectionManager->client()->Move({
      .direction = {1, 0},
  });
  if (!res) {
    std::cerr << "Failed to move right" << std::endl;
  }
}

void PlayerSystem::ProcessPlayerShoot() {
  auto res = context_.serverConnectionManager->client()->Shoot({
      .type = sdk::game::types::ProjectileType::kPlayerCommon,
  });
  if (!res) {
    std::cerr << "Failed to shoot" << std::endl;
  }
}
