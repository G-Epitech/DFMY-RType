/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** game.cpp
*/

#include "game.hpp"

#include <utility>

#include "core/components/position/position.hpp"
#include "physics/2d/systems/collision/collision_system.hpp"
#include "physics/2d/systems/movement/movement_system.hpp"
#include "physics/2d/systems/position/position_system.hpp"
#include "sets/drawable/components/components.hpp"
#include "sets/drawable/systems/drawable_system.hpp"
#include "systems/move.hpp"
#include "systems/obstacles.hpp"

using namespace zygarde::core::components;
using namespace mew::sets;

SceneGame::SceneGame(DependenciesHandler::Ptr services)
    : SceneBase(std::move(services)), deltaTime_(0) {
  registry_->RegisterComponent<Tags>();
  registry_->RegisterComponent<physics::components::Rigidbody2D>();
  registry_->RegisterComponent<physics::components::BoxCollider2D>();
  registry_->AddSystem<physics::systems::MovementSystem>(deltaTime_);
  registry_->AddSystem<physics::systems::CollisionSystem>();
  registry_->AddSystem<physics::systems::PositionSystem>();
  registry_->AddSystem<MoveSystem>(managers_.window);
  registry_->AddSystem<ObstablesSystem>(managers_.scenes, deltaTime_);
}

void SceneGame::OnCreate() {
  CreatePlayerEntity();
}

void SceneGame::Update(DeltaTime delta_time) {
  deltaTime_ = delta_time;
  registry_->RunSystems();
}

void SceneGame::CreatePlayerEntity() {
  const auto player = registry_->SpawnEntity();
  const core::types::Vector3f position{400, 400, 0};
  auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(player, Position{position, aligns});
  registry_->AddComponent<Tags>(player, Tags{{"player"}});
  registry_->AddComponent<BoxCollider2D>(
      player, physics::components::BoxCollider2D(core::types::Vector2f(50, 50)));
  registry_->AddComponent<physics::components::Rigidbody2D>(player,
                                                            physics::components::Rigidbody2D{});
  registry_->AddComponent<drawable::Drawable>(player, {.drawable =
                                                           drawable::Rectangle{
                                                               .fillColor = sf::Color::Green,
                                                               .outlineColor = sf::Color::Black,
                                                               .outlineThickness = 0,
                                                               .size = {50, 50},
                                                           },
                                                       .view = mew::managers::WindowManager::GAME,
                                                       .layer = 10});
}
