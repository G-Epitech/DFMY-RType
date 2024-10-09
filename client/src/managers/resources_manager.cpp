/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** resources_manager.cpp
*/

#include "resources_manager.hpp"

using namespace rtype::client;

ResourcesManager::ResourcesManager() = default;

ResourcesManager::~ResourcesManager() = default;

ResourcesManager::Exception::Exception(std::string msg) : msg_{std::move(msg)} {}

const char *ResourcesManager::Exception::what() const noexcept {
  return msg_.c_str();
}
