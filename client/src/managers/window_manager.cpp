/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** window_manager.cpp
*/

#include "window_manager.hpp"

#include <iostream>

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
  const sf::Vector2f center = {static_cast<float>(static_cast<float>(1920) / 2.0),
                               static_cast<float>(static_cast<float>(1080) / 2.0)};
  hudView_.setCenter(center);
  gameView_.setCenter(center);
}

WindowManager::Ptr WindowManager::Create(WindowManager::Properties&& props) {
  return std::make_shared<WindowManager>(std::move(props));
}

void WindowManager::DeferEvents() {
  sf::Event event{};

  while (window_->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window_->close();
    } else if (event.type == sf::Event::Resized) {
      HandleResize(event);
    } else {
      deferredEvents_.push_back(event);
    }
  }
}

bool WindowManager::IsActive() const {
  return window_ && window_->isOpen();
}

const WindowManager::EventsDeferrer& WindowManager::GetDeferredEvents() {
  return deferredEvents_;
}


void WindowManager::HandleResize(const sf::Event& event) {
  const sf::Vector2f size = {static_cast<float>(event.size.width),
                             static_cast<float>(event.size.height)};
  const auto widht = event.size.width / 1920.0;
  const auto height = event.size.height / 1080.0;

  gameView_.setSize(size);
  hudView_.setSize(size);
  if (widht < height) {
    hudView_.zoom(static_cast<float>(1920.0 / event.size.width));
  } else {
    hudView_.zoom(static_cast<float>(1080.0 / event.size.height));
  }
}

void WindowManager::SetGameView() const {
  window_->setView(gameView_);
}

void WindowManager::SetHUDView() const {
  window_->setView(hudView_);
}
