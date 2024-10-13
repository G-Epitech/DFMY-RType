/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** enemy_manager.cpp
*/

#include "enemy_manager.hpp"

#include <iostream>
#include <random>

void rtype::server::game::EnemyManager::Update(const utils::Timer::Nanoseconds &deltaTime,
                                               zygarde::Registry::Const_Ptr registry) {
  accumulatedTime_ += deltaTime;
  if (accumulatedTime_ < std::chrono::milliseconds(1000)) {
    return;
  }
  accumulatedTime_ = std::chrono::milliseconds(0);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dist(100.0f, 800.0f);

  zygarde::core::types::Vector3f position(500, dist(gen), 0);
  EnemyFactory::CreateEnemy(registry, position, sdk::game::types::EnemyType::kPata);
}
