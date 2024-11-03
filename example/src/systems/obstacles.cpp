/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** obstacles.cpp
*/

#include "obstacles.hpp"

#include "sets/drawable/systems/drawable_system.hpp"

ObstablesSystem::ObstablesSystem(mew::managers::ScenesManager::Ptr scenesManager,
                                 const zygarde::utils::Timer::Nanoseconds& delta_time)
    : delta_time{delta_time}, scenesManager_{std::move(scenesManager)} {
  clock_.restart();
}

void ObstablesSystem::Run(Registry::Ptr r, ZippedComponents components) {
  if (clock_.getElapsedTime() > sf::seconds(1)) {
    clock_.restart();
    CreateObstacle(r);
  }

  for (auto&& [tags, rigidbody, collider] : components) {
    if (tags & "player") {
      if (collider.HasCollision()) {
        scenesManager_->Quit();
      }
    }
  }
}

void ObstablesSystem::CreateObstacle(Registry::Ptr r) {
  const auto player = r->SpawnEntity();
  // Random number between 0 abd 800
  const auto randomX = rand() % 800;
  const core::types::Vector3f position{static_cast<float>(randomX), 0, 0};
  auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};

  r->AddComponent<Position>(player, Position{position, aligns});
  r->AddComponent<BoxCollider2D>(player,
                                 physics::components::BoxCollider2D(core::types::Vector2f(50, 50)));
  r->AddComponent<physics::components::Rigidbody2D>(
      player, physics::components::Rigidbody2D{core::types::Vector2f(0, 1000)});
  ;
  r->AddComponent<mew::sets::drawable::Drawable>(player,
                                                 {.drawable =
                                                      mew::sets::drawable::Rectangle{
                                                          .fillColor = sf::Color::Red,
                                                          .outlineColor = sf::Color::Black,
                                                          .outlineThickness = 0,
                                                          .size = {50, 50},
                                                      },
                                                  .view = mew::managers::WindowManager::GAME,
                                                  .layer = 10});
}
