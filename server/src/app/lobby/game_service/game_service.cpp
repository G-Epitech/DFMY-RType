/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** GameService.cpp
*/

#include "game_service.hpp"

#include <iostream>
#include <thread>

using namespace rtype::server::game;

GameService::GameService(const size_t& tick_rate) : ticksManager_{tick_rate} {}

void GameService::Run() {
  ticksManager_.Initialize();

  while (gameRunning_) {
    ticksManager_.Update();
    ExecuteGameLogic();
    ticksManager_.WaitUntilNextTick();
  }
}

void GameService::ExecuteGameLogic() const {
  std::cout << "Game logic executed" << gameRunning_ << std::endl;
}
