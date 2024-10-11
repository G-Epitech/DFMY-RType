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

WindowManager::WindowManager(WindowManager::Properties&& props) : props_(props) {
  window_ = std::make_shared<sf::RenderWindow>(props.videoMode, props.title, props.style,
                                               props.contextSettings);
  if (props.iconPath) {
    if (icon_.loadFromFile(*props.iconPath)) {
      window_->setIcon(icon_.getSize().x, icon_.getSize().y, icon_.getPixelsPtr());
    } else {
      std::cerr << "[ERROR]: Failed to load icon: " << *props.iconPath << std::endl;
    }
  }
  width_ = static_cast<float>(props.videoMode.width);
  height_ = static_cast<float>(props.videoMode.height);
  const sf::Vector2f center = {width_ / 2, height_ / 2};
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
  const auto width = static_cast<float>(event.size.width);
  const auto height = static_cast<float>(event.size.height);
  const sf::Vector2f size = {width, height};
  const auto widthRatio = width / width_;
  const auto heightRatio = height / height_;

  gameView_.setSize(size);
  hudView_.setSize(size);
  if (widthRatio < heightRatio) {
    hudView_.zoom(width_ / width);
  } else {
    hudView_.zoom(height_ / height);
  }
}

void WindowManager::SetView(const View& view) const {
  switch (view) {
    case GAME:
      window_->setView(gameView_);
      break;
    case HUD:
      window_->setView(hudView_);
      break;
  }
}

sf::Uint32 WindowManager::GetStyle() const {
  return props_.style;
}

void WindowManager::SetStyle(const sf::Uint32& style) {
  if (style == props_.style) {
    return;
  }
  props_.style = style;
  window_->create(props_.videoMode, props_.title, props_.style);
}
