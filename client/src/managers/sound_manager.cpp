/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** sound_manager.cpp
*/

#include "sound_manager.hpp"

#include <SFML/Audio/Sound.hpp>

using namespace rtype::client;

SoundManager::SoundManager() = default;

SoundManager::Ptr SoundManager::Create() {
  return std::make_shared<SoundManager>();
}

void SoundManager::LoadSoundBuffer(const std::string &path, const std::string &name) {
  const auto buffer = std::make_shared<sf::SoundBuffer>();
  buffer->loadFromFile(path);
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
