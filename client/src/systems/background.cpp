/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** background.cpp
*/

#include "background.hpp"

#include <iostream>
#include <random>

#include "app/app.hpp"
#include "components/drawable.hpp"
#include "core/components/position/position.hpp"

using namespace rtype::client::systems;

BackgroundSystem::BackgroundSystem() {
  clock_.restart();
}

void BackgroundSystem::Run(const std::shared_ptr<Registry> r,
                           const sparse_array<core::components::Tags>::ptr tags,
                           const sparse_array<core::components::Position>::ptr positions) {
  const float deltaTime = clock_.restart().asSeconds();

  if (tags->size() < 50) {
    SpawnStar(r);
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> speedDist(100.0f, 200.0f);

  for (size_t i = 0; i < tags->size() && i < positions->size(); ++i) {
    if ((*positions)[i] && ((*tags)[i] && (*tags)[i].value() & "background")) {
      auto& position = (*positions)[i].value();
      const float speed = speedDist(gen);

      position.point.x -= speed * deltaTime;

      if (position.point.x < -100) {
        position.point.x = static_cast<float>(2000 + (gen() % 200));
        position.point.y = static_cast<float>(gen() % APP_WINDOW_HEIGHT);
      }
    }
  }
}

void BackgroundSystem::SpawnStar(const std::shared_ptr<Registry>& r) {
  const auto entity = r->SpawnEntity();

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> disX(0, APP_WINDOW_WIDTH);
  std::uniform_int_distribution<> disY(0, APP_WINDOW_HEIGHT);
  std::uniform_real_distribution<float> disSize(1.0f, 3.0f);

  const auto randomX = static_cast<float>(disX(gen));
  const auto randomY = static_cast<float>(disY(gen));
  float randomSize = disSize(gen);

  r->AddComponent<zygarde::core::components::Position>(
      entity, {core::types::Vector3f{randomX, randomY, 0}});
  r->AddComponent<core::components::Tags>(entity, core::components::Tags({"background"}));
  r->AddComponent<rtype::client::components::Drawable>(entity, {components::Rectangle{
                                                                   .color = sf::Color::White,
                                                                   .size = {randomSize, randomSize},
                                                               }});
}
