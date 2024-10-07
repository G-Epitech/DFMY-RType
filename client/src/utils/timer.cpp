/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** timer.cpp
*/

#include "timer.hpp"

using namespace rtype::client::utils;

Timer::Timer() {
    this->operator++();
}

DeltaTime Timer::operator++() {
  auto now = std::chrono::high_resolution_clock::now();
  auto diff = now - _last;

  _last = now;
  return diff;
}

DeltaTime Timer::GetElapsedTime() const {
  return std::chrono::high_resolution_clock::now() - _last;
}
