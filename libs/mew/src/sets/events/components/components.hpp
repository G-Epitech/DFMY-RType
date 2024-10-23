/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** on_event.hpp
*/

#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <functional>

#include "libs/mew/src/sets/events/constants.hpp"

namespace mew::sets::events {
template <EventType T>
struct OnEventHandler;

template <>
struct OnEventHandler<kKeyPressed> {
  using signature = std::function<void(sf::Keyboard::Key)>;
};

template <>
struct OnEventHandler<kKeyReleased> {
  using signature = std::function<void(sf::Keyboard::Key)>;
};

template <>
struct OnEventHandler<kMousePressed> {
  using signature = std::function<void(sf::Mouse::Button, sf::Vector2f, MouseEventTarget)>;
};

template <>
struct OnEventHandler<kMouseReleased> {
  using signature = std::function<void(sf::Mouse::Button, sf::Vector2f, MouseEventTarget)>;
};

template <>
struct OnEventHandler<kMouseMoved> {
  using signature = std::function<void(sf::Vector2f, MouseEventTarget)>;
};

template <>
struct OnEventHandler<kMouseScrolled> {
  using signature = std::function<void(sf::Vector2f, float)>;
};

template <EventType T>
struct OnEvent {
  using Handler = OnEventHandler<T>::signature;
  Handler handler = Handler();  /// @brief Function to call when the event is triggered
};

template <>
struct OnEvent<kMousePressed> {
  using Handler = OnEventHandler<kMousePressed>::signature;

  MouseEventTarget strategy =
      kLocalTarget;  /// @brief Strategy to determine which entities will receive the event
  Handler handler = Handler();  /// @brief Function to call when the event is triggered
};

template <>
struct OnEvent<kMouseReleased> {
  using Handler = OnEventHandler<kMouseReleased>::signature;

  MouseEventTarget strategy =
      kLocalTarget;  /// @brief Strategy to determine which entities will receive the event
  Handler handler = Handler();  /// @brief Function to call when the event is triggered
};

template <>
struct OnEvent<kMouseMoved> {
  using Handler = OnEventHandler<kMouseMoved>::signature;

  MouseEventTarget strategy =
      kAnyTarget;  /// @brief Strategy to determine which entities will receive the event
  Handler handler = Handler();  /// @brief Function to call when the event is triggered
};

typedef OnEvent<kKeyPressed> OnKeyPressed;
typedef OnEvent<kKeyReleased> OnKeyReleased;
typedef OnEvent<kMousePressed> OnMousePressed;
typedef OnEvent<kMouseReleased> OnMouseReleased;
typedef OnEvent<kMouseMoved> OnMouseMoved;
typedef OnEvent<kMouseScrolled> OnMouseScrolled;

}  // namespace mew::sets::events
