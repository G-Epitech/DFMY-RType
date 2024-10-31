/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** TicksManager.cpp
*/

#include "ticks_manager.hpp"

#include <iostream>
#include <thread>

using namespace rtype::server::game;

TicksManager::TicksManager(const size_t& tick_rate)
    : tickRate_{tick_rate}, millisecondsPerTick_(), logger_("server_tick_manager") {
  millisecondsPerTick_ = std::chrono::milliseconds(1000 / tickRate_);
}

void TicksManager::WaitUntilNextTick() {
  timer_.RefreshDeltaTime();
  auto& deltaTime = timer_.GetDeltaTime();
  auto deltaTimeInMs = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count();

  auto waitTime = millisecondsPerTick_.count() - deltaTimeInMs;
  LogWaitTime(waitTime);
  if (waitTime > 0) {
    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
  }
}

void TicksManager::LogWaitTime(long wait_time) {
  auto count = millisecondsPerTick_.count();
  if (wait_time > count) {
    logger_.Warning("Wait time is higher than the tick rate", "⚠️");
  }
  logger_.Info("Wait time: " + std::to_string(wait_time) + "/" + std::to_string(count), "⏳");
}
