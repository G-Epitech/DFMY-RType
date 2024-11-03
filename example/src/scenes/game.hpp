/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** game.hpp
*/

#pragma once

#include "libs/zygarde/src/utils/timer/timer.hpp"
#include "scenes/scene_base.hpp"

using namespace mew::scenes;

class SceneGame final : public SceneBase {
 public:
  explicit SceneGame(DependenciesHandler::Ptr services);
  ~SceneGame() override = default;

  void Update(DeltaTime delta_time) override;

 protected:
  void OnCreate() override;

 private:
  void CreatePlayerEntity();

  zygarde::utils::Timer::Nanoseconds deltaTime_;
};
