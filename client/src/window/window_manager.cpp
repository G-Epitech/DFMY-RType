/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** window_manager.cpp
*/

#include <iostream>

#include "window_manager.hpp"

using namespace rtype::client;

void WindowManager::ClearEvents() noexcept {
  deferredEvents_.clear();
}

WindowManager::WindowManager(WindowManager::Properties&& props) {
  window_ = std::make_shared<sf::RenderWindow>(props.videoMode, props.title, props.style,
                                               props.contextSettings);
  if (props.iconPath) {
    if (icon_.loadFromFile(*props.iconPath)) {
      window_->setIcon(icon_.getSize().x, icon_.getSize().y, icon_.getPixelsPtr());
    } else {
      std::cerr << "[ERROR]: Failed to load icon: " << *props.iconPath << std::endl;
    }
  }
}

WindowManager::Ptr WindowManager::Create(WindowManager::Properties&& props) {
  return std::make_shared<WindowManager>(std::move(props));
}

void WindowManager::DeferEvents() {
  sf::Event event{};

  while (window_->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window_->close();
    } else {
      deferredEvents_.push_back(event);
    }
  }
}
