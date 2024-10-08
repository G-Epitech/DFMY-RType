/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Timer.cpp
*/

#include "timer.hpp"

using namespace zygarde::utils;

void Timer::Update() noexcept {
  deltaTime_ = std::chrono::duration_cast<Nanoseconds>(Now() - lastTimePoint_);
  lastTimePoint_ = Now();
}

void Timer::Initialize() noexcept {
  lastTimePoint_ = Now();
}

double Timer::ToSeconds(Timer::Nanoseconds nanoseconds) noexcept {
  return std::chrono::duration<double>(nanoseconds).count();
}

Timer::TimePoint Timer::Now() noexcept {
  return std::chrono::high_resolution_clock::now();
}
