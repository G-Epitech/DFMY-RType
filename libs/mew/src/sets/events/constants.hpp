/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** constants.hpp
*/

#pragma once

#include <SFML/Window/Event.hpp>

namespace mew::sets::events {
enum EventType {
  kNone,           ///< @brief No event
  kKeyPressed,     ///< @brief Called when a key is pressed
  kKeyReleased,    ///< @brief Called when a key is released
  kMousePressed,   ///< @brief Called when a mouse button is pressed
  kMouseReleased,  ///< @brief Called when a mouse button is released
  kMouseMoved,     ///< @brief Called when the mouse is moved
  kMouseScrolled,  ///< @brief Called when the mouse wheel is scrolled
  kTextEntered,    ///< @brief Called when a text is entered
};

/// @brief Strategy to determine which entities will receive the event
enum MouseEventTarget {
  kNoTarget = 0,     ///< @brief Undefined target
  kLocalTarget = 1,  ///< @brief Only the entity that has the component will receive the event
  kOtherTarget = 2,  ///< @brief All entities except the one that has the component will receive
                     ///< the event
  kAnyTarget = kLocalTarget | kOtherTarget,  ///< @brief All entities will receive the event
};

template <EventType T>
struct EventTypeMapper;

template <>
struct EventTypeMapper<kKeyPressed> {
  static constexpr sf::Event::EventType type = sf::Event::EventType::KeyPressed;
};

template <>
struct EventTypeMapper<kKeyReleased> {
  static constexpr sf::Event::EventType type = sf::Event::EventType::KeyReleased;
};

template <>
struct EventTypeMapper<kMousePressed> {
  static constexpr sf::Event::EventType type = sf::Event::EventType::MouseButtonPressed;
};

template <>
struct EventTypeMapper<kMouseReleased> {
  static constexpr sf::Event::EventType type = sf::Event::EventType::MouseButtonReleased;
};

template <>
struct EventTypeMapper<kMouseMoved> {
  static constexpr sf::Event::EventType type = sf::Event::EventType::MouseMoved;
};

template <>
struct EventTypeMapper<kMouseScrolled> {
  static constexpr sf::Event::EventType type = sf::Event::EventType::MouseWheelScrolled;
};

template <>
struct EventTypeMapper<kTextEntered> {
  static constexpr sf::Event::EventType type = sf::Event::EventType::TextEntered;
};

}  // namespace mew::sets::events
