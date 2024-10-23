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

  auto normalShader = std::make_shared<sf::Shader>();
  normalShader->loadFromFile("assets/shaders/normal.frag", sf::Shader::Fragment);
  shaders_["normal"] = normalShader;
  auto protanopiaShader = std::make_shared<sf::Shader>();
  protanopiaShader->loadFromFile("assets/shaders/protanopia.frag", sf::Shader::Fragment);
  shaders_["protanopia"] = protanopiaShader;
  auto deuteranopiaShader = std::make_shared<sf::Shader>();
  deuteranopiaShader->loadFromFile("assets/shaders/deuteranopia.frag", sf::Shader::Fragment);
  shaders_["deuteranopia"] = deuteranopiaShader;
  auto tritanopiaShader = std::make_shared<sf::Shader>();
  tritanopiaShader->loadFromFile("assets/shaders/tritanopia.frag", sf::Shader::Fragment);
  shaders_["tritanopia"] = tritanopiaShader;
  selectedShader_ = normalShader;
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
    hudView_.zoom(height / height);
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

void WindowManager::SetShader(const std::string& name) {
  auto shader = shaders_.find(name);
  if (shader != shaders_.end()) {
    selectedShader_ = shader->second;
  } else {
    std::cerr << "[ERROR]: Shader not found: " << name << std::endl;
  }
}

std::shared_ptr<sf::Shader> WindowManager::GetSelectedShader() const {
  return selectedShader_;
}
