/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** my_scene.hpp
*/

#pragma once

#include "scenes/scene_interface.hpp"

namespace rtype::client {
class MyScene : public IScene {
 public:
  MyScene();
  ~MyScene() override = default;

  void Run() override;

 protected:
  void InjectGlobalContext(GlobalContext::Ptr globalContext) override;
  GlobalContext::Ptr _globalContext;
};
}  // namespace rtype::client
