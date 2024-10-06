/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** my_scene.hpp
*/

#pragma once

#include "context/global_context.hpp"
#include "scenes/scene_base.hpp"

namespace rtype::client {
class MyScene : public SceneBase<GlobalContext> {
 public:
  explicit MyScene(const GlobalContext &context);
  ~MyScene() override = default;

  void Draw() override;

  void Update(utils::DeltaTime delta_time) override;

 protected:
  unsigned int counter_ = 0;
};
}  // namespace rtype::client
