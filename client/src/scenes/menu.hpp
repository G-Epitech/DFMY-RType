/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** my_scene.hpp
*/

#pragma once

#include "bases/scene_base.hpp"
#include "context/global_context.hpp"
#include "managers/resources_manager.hpp"

namespace rtype::client {
class SceneMenu final : public SceneBase<GlobalContext> {
 public:
  explicit SceneMenu(const GlobalContext &context);
  ~SceneMenu() override = default;

  void Draw() override;

  void Update(utils::DeltaTime delta_time) override;

 protected:
  unsigned int counter_ = 0;
  ResourcesManager resourcesManager_;
};
}  // namespace rtype::client
