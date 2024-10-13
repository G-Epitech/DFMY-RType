/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** keymap.cpp
*/

#include "keymap.hpp"

using namespace rtype::client;

KeyMap const KeyMap::ZQSD = {
    .schema = KeyMapSchema::kKeyMapZQSD,
    .controls =
        std::map<GameAction, GameControl>{
            {GameAction::kActionUp, {GameControlType::kControlKeyboard, {.key = sf::Keyboard::Z}}},
            {GameAction::kActionDown,
             {GameControlType::kControlKeyboard, {.key = sf::Keyboard::S}}},
            {GameAction::kActionLeft,
             {GameControlType::kControlKeyboard, {.key = sf::Keyboard::Q}}},
            {GameAction::kActionRight,
             {GameControlType::kControlKeyboard, {.key = sf::Keyboard::D}}},
            {GameAction::kActionShoot,
             {GameControlType::kControlKeyboard, {.key = sf::Keyboard::Space}}},
        },
};

KeyMap const KeyMap::Arrows = {
    .schema = KeyMapSchema::kKeyMapArrows,
    .controls =
        std::map<GameAction, GameControl>{
            {GameAction::kActionUp, {GameControlType::kControlKeyboard, {.key = sf::Keyboard::Up}}},
            {GameAction::kActionDown,
             {GameControlType::kControlKeyboard, {.key = sf::Keyboard::Down}}},
            {GameAction::kActionLeft,
             {GameControlType::kControlKeyboard, {.key = sf::Keyboard::Left}}},
            {GameAction::kActionRight,
             {GameControlType::kControlKeyboard, {.key = sf::Keyboard::Right}}},
            {GameAction::kActionShoot,
             {GameControlType::kControlKeyboard, {.key = sf::Keyboard::Space}}},
        },
};

bool KeyMap::operator==(const KeyMap& other) const {
  for (const auto& [action, control] : controls) {
    if (other.controls.find(action) == other.controls.end()) {
      return false;
    }
    if (control.type != other.controls.at(action).type) {
      return false;
    }
    switch (control.type) {
      case GameControlType::kControlKeyboard:
        if (control.trigger.key != other.controls.at(action).trigger.key) {
          return false;
        }
        break;
      case GameControlType::kControlClickMouse:
        if (control.trigger.button != other.controls.at(action).trigger.button) {
          return false;
        }
        break;
    }
  }
  return true;
}
bool KeyMap::IsControlAvailable(GameAction action, GameControlType type,
                                GameControlTrigger trigger) const {
  auto used = true;

  for (const auto& [act, control] : controls) {
    if (control.type == type && act != action) {
      switch (type) {
        case GameControlType::kControlKeyboard:
          used &= control.trigger.key == trigger.key;
          break;
        case GameControlType::kControlClickMouse:
          used &= control.trigger.button == trigger.button;
          break;
      }
    }
  }
  return !used;
}
bool KeyMap::SetControl(GameAction action, GameControlType type, GameControlTrigger trigger) {
  if (!IsControlAvailable(action, type, trigger))
    return false;

  controls[action] = {type, trigger};

  if ((*this) == ZQSD) {
    schema = KeyMapSchema::kKeyMapZQSD;
  } else if ((*this) == Arrows) {
    schema = KeyMapSchema::kKeyMapArrows;
  } else {
    schema = KeyMapSchema::kKeyMapCustom;
  }
  return true;
}
GameAction KeyMap::GetActionFromKey(const sf::Keyboard::Key& key) const {
  for (const auto& [action, control] : controls) {
    if (control.type == GameControlType::kControlKeyboard && control.trigger.key == key) {
      return action;
    }
  }
  return GameAction::kNone;
}

GameAction KeyMap::GetActionFromMouse(const sf::Mouse::Button& button) const {
  for (const auto& [action, control] : controls) {
    if (control.type == GameControlType::kControlClickMouse && control.trigger.button == button) {
      return action;
    }
  }
  return GameAction::kNone;
}
