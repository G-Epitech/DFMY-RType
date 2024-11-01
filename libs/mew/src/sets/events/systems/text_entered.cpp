/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** text_entered.cpp
*/

#include "./text_entered.hpp"

#include <utility>

using namespace mew::sets::events;

TextEnteredEventSystem::TextEnteredEventSystem(managers::WindowManager::Ptr window_manager)
    : EventSystemBase<kTextEntered, OnTextEntered>(std::move(window_manager)) {}

TextEnteredEventSystem::~TextEnteredEventSystem() = default;

void TextEnteredEventSystem::HandleEvent(const sf::Event& event, Registry::Ptr r,
                                         zipper<OnTextEntered> components) {
  for (auto&& [textEntered] : components) {
    textEntered.handler(event.text.unicode);
  }
}
