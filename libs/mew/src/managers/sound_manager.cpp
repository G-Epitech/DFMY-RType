/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** sound_manager.cpp
*/

#include "./sound_manager.hpp"

#include <SFML/Audio/Sound.hpp>
#include <iostream>

using namespace mew::managers;

SoundManager::SoundManager(DependenciesHandler::Ptr services)
    : ManagerBase(std::move(services)) {}

void SoundManager::LoadSoundBuffer(const std::string &path, const std::string &name) {
  if (soundBuffers_.contains(name)) {
    std::cerr << "Sound buffer already loaded: " << name << std::endl;
    return;
  }
  const auto buffer = std::make_shared<sf::SoundBuffer>();
  if (!buffer->loadFromFile(path)) {
    throw Exception("Failed to load sound buffer: " + path);
  }
  soundBuffers_[name] = buffer;
}

void SoundManager::PlaySound(const std::string &name) {
  const auto buffer = soundBuffers_[name];
  const auto sound = std::make_shared<sf::Sound>(*buffer);
  sound->setVolume(soundVolume_);
  sound->play();
  sounds_.push(sound);
}

void SoundManager::PlayMusic(const std::string &path) {
  const auto music = std::make_shared<sf::Music>();
  music->openFromFile(path);
  music->setVolume(musicVolume_);
  music->play();
  musics_.push(music);
}

float SoundManager::GetSoundVolume() const {
  return soundVolume_;
}

float SoundManager::GetMusicVolume() const {
  return musicVolume_;
}

void SoundManager::SetSoundVolume(const float &volume) {
  soundVolume_ = volume;
}

void SoundManager::SetMusicVolume(const float &volume) {
  musicVolume_ = volume;
}

SoundManager::Exception::Exception(std::string message) : message_{std::move(message)} {}

const char *SoundManager::Exception::what() const noexcept {
  return message_.c_str();
}
