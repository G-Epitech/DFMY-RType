/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** my_scene.hpp
*/

#pragma once

#include "scenes/scene_base.hpp"

namespace rtype::client {
class MyScene : public SceneBase {
 public:
  explicit MyScene(const GlobalContext &global_context);
  ~MyScene() override = default;

  void Draw() override;

  void Update(utils::DeltaTime delta_time) override;

 protected:
  uint counter_ = 0;
};
}  // namespace rtype::client
