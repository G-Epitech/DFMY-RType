/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** player.cpp
*/

#include "player.hpp"

#include <iostream>

using namespace rtype::client::systems;

PlayerSystem::PlayerSystem(const WindowManager::Ptr &window_manager,
                           const GameManager::Ptr &game_manager)
    : windowManager_{window_manager}, gameManager_{game_manager} {}

void PlayerSystem::Run(Registry::Ptr r) {
  const auto events = windowManager_->GetDeferredEvents();

  // If a key is pressed, we send a message to the server
  for (const auto &event : events) {
    const auto actionKeyBoard = gameManager_->keyMap.GetActionFromKey(event.key.code);
    const auto actionMouse = gameManager_->keyMap.GetActionFromMouse(event.mouseButton.button);
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
  std::cout << "Move up" << std::endl;
}

void PlayerSystem::ProcessPlayerMoveDown() {
  std::cout << "Move down" << std::endl;
}

void PlayerSystem::ProcessPlayerMoveLeft() {
  std::cout << "Move left" << std::endl;
}

void PlayerSystem::ProcessPlayerMoveRight() {
  std::cout << "Move right" << std::endl;
}

void PlayerSystem::ProcessPlayerShoot() {
  std::cout << "Shoot" << std::endl;
}
