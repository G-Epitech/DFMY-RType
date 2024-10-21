/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** enemy_manager.cpp
*/

#include "enemy_manager.hpp"

#include <random>

void rtype::server::game::EnemyManager::Update(const utils::Timer::Nanoseconds &delta_time,
                                               Registry::Const_Ptr registry) {
  accumulatedTime_ += delta_time;

  if (accumulatedTime_ < std::chrono::milliseconds(4000)) {
    return;
  }
  accumulatedTime_ = std::chrono::milliseconds(0);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution dist(80.0f, 1000.0f);

  const core::types::Vector3f position(2000, dist(gen), 0);
  EnemyFactory::CreateEnemy(registry, position, sdk::game::types::EnemyType::kPata);
}
