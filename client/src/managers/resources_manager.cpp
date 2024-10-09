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

void ResourcesManager::LoadFont(const std::string &path, const std::string &name) {
  if (resourcesMap_.fonts.contains(name)) {
    throw Exception("Font already loaded");
  }
  sf::Font font;
  if (!font.loadFromFile(path)) {
    throw Exception("Failed to load font");
  }
  resourcesMap_.fonts[name] = font;
}

void ResourcesManager::LoadTexture(const std::string &path, const std::string &name) {
  if (resourcesMap_.textures.contains(name)) {
    throw Exception("Texture already loaded");
  }
  sf::Texture texture;
  if (!texture.loadFromFile(path)) {
    throw Exception("Failed to load texture");
  }
  resourcesMap_.textures[name] = texture;
}

void ResourcesManager::LoadSound(const std::string &path, const std::string &name) {
  if (resourcesMap_.sounds.contains(name)) {
    throw Exception("Sound already loaded");
  }
  sf::SoundBuffer sound;
  if (!sound.loadFromFile(path)) {
    throw Exception("Failed to load sound");
  }
  resourcesMap_.sounds[name] = sound;
}

sf::Texture &ResourcesManager::GetTexture(const std::string &name) {
  if (!resourcesMap_.textures.contains(name)) {
    throw Exception("Texture not found");
  }
  return resourcesMap_.textures[name];
}

sf::Font &ResourcesManager::GetFont(const std::string &name) {
  if (!resourcesMap_.fonts.contains(name)) {
    throw Exception("Font not found");
  }
  return resourcesMap_.fonts[name];
}

sf::SoundBuffer &ResourcesManager::GetSound(const std::string &name) {
  if (!resourcesMap_.sounds.contains(name)) {
    throw Exception("Sound not found");
  }
  return resourcesMap_.sounds[name];
}
