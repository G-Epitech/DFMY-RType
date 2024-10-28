/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** background.cpp
*/

#include "background.hpp"

#include <iostream>
#include <random>

#include "client/src/constants/window.hpp"
#include "libs/mew/src/sets/drawable/drawable.hpp"

using namespace rtype::client::systems;
using namespace mew::sets::drawable;
using namespace zygarde::core::components;
using namespace zygarde::core::types;

BackgroundSystem::BackgroundSystem() : starsCount_(0) {
  clock_.restart();
}

void BackgroundSystem::Run(const std::shared_ptr<Registry> r, zipper<Tags, Position> components) {
  const float deltaTime = clock_.restart().asSeconds();
  if (starsCount_ < 50) {
    SpawnStar(r);
    starsCount_ += 1;
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> speedDist(100.0f, 200.0f);

  for (auto&& [tag, position] : components) {
    if (!(tag & "background")) {
      continue;
    }
    const float speed = speedDist(gen);

    position.point.x -= speed * deltaTime;

    if (position.point.x < -100) {
      position.point.x = static_cast<float>(2000 + (gen() % 200));
      position.point.y = static_cast<float>(gen() % APP_WINDOW_HEIGHT);
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

  r->AddComponent<Position>(entity, {Vector3f{randomX, randomY, 0}});
  r->AddComponent<Tags>(entity, Tags({"background"}));
  r->AddComponent<Drawable>(entity, {Rectangle{
                                        .color = sf::Color::White,
                                        .size = {randomSize, randomSize},
                                    }});
}
