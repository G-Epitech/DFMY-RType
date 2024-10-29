/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** enemy_manager.hpp
*/

#pragma once

#include "app/room/game_service/factories/enemy_factory.hpp"
#include "zygarde/src/registry.hpp"
#include "zygarde/src/utils/timer/timer.hpp"

namespace rtype::server::game {
class EnemyManager {
 public:
  EnemyManager() = default;
  ~EnemyManager() = default;

  void Update(const zygarde::utils::Timer::Nanoseconds &delta_time,
              zygarde::Registry::Const_Ptr registry);

 private:
  zygarde::utils::Timer::Nanoseconds accumulatedTime_;
};
}  // namespace rtype::server::game