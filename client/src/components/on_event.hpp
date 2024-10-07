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

namespace rtype::client::events {
enum EventType {
  kNone,               /// @brief No event
  kKeyPressed,         /// @brief Called when a key is pressed
  kKeyReleased,        /// @brief Called when a key is released
  kMousePressed,       /// @brief Called when a mouse button is pressed
  kMouseReleased,      /// @brief Called when a mouse button is released
  kMouseMoved,         /// @brief Called when the mouse is moved
  kMouseWheelScrolled  /// @brief Called when the mouse wheel is scrolled
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
struct EventTypeMapper<kMouseWheelScrolled> {
  static constexpr sf::Event::EventType type = sf::Event::EventType::MouseWheelScrolled;
};
}  // namespace rtype::client::events

namespace rtype::client::components {
template <events::EventType T>
struct OnEventHandler;

template <>
struct OnEventHandler<events::kKeyPressed> {
  using signature = std::function<void(sf::Keyboard::Key)>;
};

template <>
struct OnEventHandler<events::kKeyReleased> {
  using signature = std::function<void(sf::Keyboard::Key)>;
};

template <>
struct OnEventHandler<events::kMousePressed> {
  using signature = std::function<void(sf::Mouse::Button, sf::Vector2i)>;
};

template <>
struct OnEventHandler<events::kMouseReleased> {
  using signature = std::function<void(sf::Mouse::Button, sf::Vector2i)>;
};

template <>
struct OnEventHandler<events::kMouseMoved> {
  using signature = std::function<void(sf::Vector2i)>;
};

template <>
struct OnEventHandler<events::kMouseWheelScrolled> {
  using signature = std::function<void(sf::Vector2i, float)>;
};

template <events::EventType T>
struct OnEvent {
  using Handler = OnEventHandler<T>::signature;
  Handler handler;
};

typedef OnEvent<events::kKeyPressed> OnKeyPressed;
typedef OnEvent<events::kKeyReleased> OnKeyReleased;
typedef OnEvent<events::kMousePressed> OnMousePressed;
typedef OnEvent<events::kMouseReleased> OnMouseReleased;
typedef OnEvent<events::kMouseMoved> OnMouseMoved;
typedef OnEvent<events::kMouseWheelScrolled> OnMouseWheelScrolled;

}  // namespace rtype::client::components
