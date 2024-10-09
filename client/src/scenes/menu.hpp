/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** my_scene.hpp
*/

#pragma once

#include "bases/scene_base.hpp"
#include "context/global_context.hpp"

namespace rtype::client {
class SceneMenu final : public SceneBase<GlobalContext> {
 public:
  explicit SceneMenu(const GlobalContext &context);
  ~SceneMenu() override = default;

  void Update(utils::DeltaTime delta_time) override;

  void OnCreate() override;

  void OnActivate() override;

 protected:
  unsigned int counter_ = 0;
  std::size_t e{};
};
}  // namespace rtype::client
