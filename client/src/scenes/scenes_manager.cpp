/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** scene_manager.cpp
*/

#include "scenes_manager.hpp"

#include <utility>

using namespace rtype::client;

ScenesManager::ScenesManager(const GlobalContext& context) : context_{context} {}

ScenesManager::Exception::Exception(std::string msg) : msg_{std::move(msg)} {}

const char* ScenesManager::Exception::what() const noexcept {
  return msg_.c_str();
}
