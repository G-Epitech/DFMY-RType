/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** blink.cpp
*/

#include "blink.hpp"

rtype::client::systems::BlinkSystem::BlinkSystem() {
  clock_.restart();
}

void rtype::client::systems::BlinkSystem::Run(std::shared_ptr<Registry> r,
                                              ZippedComponents components) {
  const auto begin = components.begin();
  const auto end = components.end();

  for (auto it = begin; it != end; ++it) {
    const auto [entity, component] = ~it;
    const auto [tags, drawable] = component;

    if (tags & "blink") {
      if (tags & "disabled") {
        drawable.visible = false;
        continue;
      }
      if (tags & "not_blink") {
        if (!entitiesNotBlink_.contains(entity)) {
          entitiesNotBlink_[entity] = clock_.getElapsedTime();
        }

        if (clock_.getElapsedTime() - entitiesNotBlink_[entity] > sf::seconds(1.0f)) {
          tags.RemoveTag("not_blink");
          entitiesNotBlink_.erase(entity);
        }
      } else {
        if (!entities_.contains(entity)) {
          entities_[entity] = clock_.getElapsedTime();
        }

        if (clock_.getElapsedTime() - entities_[entity] > sf::seconds(0.5f)) {
          entities_[entity] = clock_.getElapsedTime();
          drawable.visible = !drawable.visible;
        }
      }
    }
  }
}
