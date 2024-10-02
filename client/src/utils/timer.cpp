/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** timer.cpp
*/

#include "timer.hpp"

using namespace rtype::client::utils;

Timer::Timer() {
  tick();
}

void Timer::tick() {
  _last = std::chrono::high_resolution_clock::now();
}

DeltaTime Timer::GetElapsedTime() const {
  return std::chrono::high_resolution_clock::now() - _last;
}
