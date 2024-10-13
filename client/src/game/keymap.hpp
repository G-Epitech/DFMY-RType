/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** keymap.hpp
*/

#pragma once

#include <variant>

#include "systems/events/key.hpp"
namespace rtype::client {
enum class GameAction {
  kNone = 0,     ///< No action
  kActionUp,     ///< Up control
  kActionDown,   ///< Down control
  kActionLeft,   ///< Left control
  kActionRight,  ///< Right control
  kActionShoot,  ///< Shoot control
};

enum class GameControlType {
  kControlKeyboard,    ///< Keyboard control
  kControlClickMouse,  ///< Mouse control
};

union GameControlTrigger {
  sf::Keyboard::Key key;     ///< Key
  sf::Mouse::Button button;  ///< Button
};

struct GameControl {
  GameControlType type;        ///< Type of the control
  GameControlTrigger trigger;  ///< Trigger of the control
};

enum class KeyMapSchema {
  kKeyMapZQSD,
  kKeyMapArrows,
  kKeyMapCustom,
};

struct KeyMap {
  KeyMapSchema schema;                         ///< Schema of the key map
  std::map<GameAction, GameControl> controls;  ///< Controls

  /**
   * @brief Compare two key maps
   * @param other Other key map
   * @return Comparison result
   */
  bool operator==(const KeyMap& other) const;

  /**
   * @brief Check if a control is available
   * @param action Action to check
   * @param type Type of control
   * @param trigger Trigger of the control
   * @return Availability of the control
   */
  [[nodiscard]] bool IsControlAvailable(GameAction action, GameControlType type,
                                        GameControlTrigger trigger) const;

  /**
   * @brief Set a control
   * @param action Action to set
   * @param type Type of control
   * @param trigger Trigger of the control
   * @return True if the control was set, false otherwise
   */
  [[nodiscard]] bool SetControl(GameAction action, GameControlType type,
                                GameControlTrigger trigger);

  /**
   * @brief Find the action corresponding to an event
   * @param event Event to map
   * @return Action corresponding to the event or kNone if no action is found
   */
  [[nodiscard]] GameAction GetActionFromKey(const sf::Keyboard::Key& key) const;

  /**
   * @brief Find the action corresponding to a button press
   * @param button Button to map
   * @return Action corresponding to the button or kNone if no action is found
   */
  [[nodiscard]] GameAction GetActionFromMouse(const sf::Mouse::Button& button) const;

  static const KeyMap ZQSD;
  static const KeyMap Arrows;
};

}  // namespace rtype::client
