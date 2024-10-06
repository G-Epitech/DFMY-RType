/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** on_event.hpp
*/

#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <functional>

namespace rtype::client::components {
enum EventType {
  kKeyPressed,         // Called when a key is pressed
  kKeyReleased,        // Called when a key is released
  kMousePressed,       // Called when a mouse button is pressed
  kMouseReleased,      // Called when a mouse button is released
  kMouseMoved,         // Called when the mouse is moved
  kMouseWheelScrolled  // Called when the mouse wheel is scrolled
};

template <EventType T>
struct OnEventHandler;  // Forward declaration

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
  using signature = std::function<void(sf::Mouse::Button, sf::Vector2i)>;
};

template <>
struct OnEventHandler<kMouseReleased> {
  using signature = std::function<void(sf::Mouse::Button, sf::Vector2i)>;
};

template <>
struct OnEventHandler<kMouseMoved> {
  using signature = std::function<void(sf::Vector2i)>;
};

template <>
struct OnEventHandler<kMouseWheelScrolled> {
  using signature = std::function<void(sf::Vector2i, float)>;
};

template <EventType T>
struct OnEvent {
  using HandlerType = typename OnEventHandler<T>::signature;
  HandlerType handler;  // Function to call when the event is triggered
};

}  // namespace rtype::client::components
