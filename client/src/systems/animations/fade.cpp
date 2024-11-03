/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** fade.cpp
*/

#include "fade.hpp"

rtype::client::systems::FadeSystem::FadeSystem() {
  deltaClock_.restart();
}

void rtype::client::systems::FadeSystem::Run(std::shared_ptr<Registry> r,
                                             ComponentsPtr components) {
  const auto begin = components.begin();
  const auto end = components.end();

  for (auto it = begin; it != end; ++it) {
    const auto [entity, component] = ~it;
    const auto [tags, drawable] = component;

    if (!(tags & "fade")) {
      continue;
    }

    if (!entities_.contains(entity)) {
      entities_[entity] = deltaClock_.getElapsedTime();
    }

    auto elapsedTime = deltaClock_.getElapsedTime() - entities_[entity];
    if (elapsedTime >= sf::milliseconds(1000 / 255)) {
      entities_[entity] = deltaClock_.getElapsedTime();

      auto &rectangle = std::get<mew::sets::drawable::Rectangle>(drawable.drawable);
      rectangle.color.a += 1;

      if (rectangle.color.a >= 255) {
        tags.RemoveTag("fade");
        entities_.erase(entity);
      }
    }
  }
}
