/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** game_manager.cpp
*/

#include "game_manager.hpp"

using namespace rtype::client;

GameManager::Ptr GameManager::Create() {
  return std::make_shared<GameManager>();
}

GameManager::GameManager() = default;

GameManager::~GameManager() = default;
