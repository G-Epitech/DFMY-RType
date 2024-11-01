/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** window_manager.cpp
*/

#include "window_manager.hpp"

#include <iostream>

using namespace mew::managers;

void WindowManager::ClearEvents() noexcept {
  deferredEvents_.clear();
}

WindowManager::WindowManager(DependenciesHandler::Ptr services,
                             const WindowManager::Properties& props)
    : ManagerBase(std::move(services)), props_(props) {
  deferredEvents_.reserve(kEventsAverageLength);
  window_ = std::make_shared<sf::RenderWindow>(props_.videoMode, props_.title, props_.style,
                                               props_.contextSettings);
  window_->setFramerateLimit(props_.frameLimit);

  if (props.iconPath) {
    if (icon_.loadFromFile(*props.iconPath)) {
      window_->setIcon(icon_.getSize().x, icon_.getSize().y, icon_.getPixelsPtr());
    } else {
      std::cerr << "[ERROR]: Failed to load icon: " << *props.iconPath << std::endl;
    }
  }

  const sf::Vector2f center = {GetWidth() / 2, GetHeight() / 2};
  hudView_.setCenter(center);
  gameView_.setCenter(center);
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
  const auto widthRatio = width / GetWidth();
  const auto heightRatio = height / GetHeight();

  gameView_.setSize(size);
  hudView_.setSize(size);
  if (widthRatio < heightRatio) {
    hudView_.zoom(GetWidth() / width);
  } else {
    hudView_.zoom(GetHeight() / height);
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

std::shared_ptr<sf::Shader> WindowManager::GetShader() const {
  return shader_;
}

void WindowManager::SetShader(std::shared_ptr<sf::Shader> shader) {
  shader_ = std::move(shader);
}
