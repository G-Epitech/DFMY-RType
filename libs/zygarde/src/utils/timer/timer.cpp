/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Timer.cpp
*/

#include "./timer.hpp"

using namespace zygarde::utils;

void Timer::Initialize() noexcept {
  lastTimePoint_ = Now();
}

void Timer::Update() noexcept {
  deltaTime_ = std::chrono::duration_cast<Nanoseconds>(Now() - lastTimePoint_);
  lastTimePoint_ = Now();
}

void Timer::RefreshDeltaTime() noexcept {
  deltaTime_ = std::chrono::duration_cast<Nanoseconds>(Now() - lastTimePoint_);
}

float Timer::ToSeconds(Timer::Nanoseconds nanoseconds) noexcept {
  return std::chrono::duration<float>(nanoseconds).count();
}
