/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** fade.hpp
*/

#pragma once
#include <SFML/System/Clock.hpp>

#include "core/components/tags/tags.hpp"
#include "sets/drawable/components/components.hpp"
#include "system_abstract.hpp"

namespace rtype::client::systems {
class FadeSystem final
    : public ASystem<zygarde::core::components::Tags, mew::sets::drawable::Drawable> {
 public:
  FadeSystem();

  void Run(std::shared_ptr<Registry> r, ZippedComponents components) override;

 private:
  /// @brief The delta clock
  sf::Clock deltaClock_;

  /// @brief Map of entities to fade
  std::map<std::size_t, sf::Time> entities_;
};
}  // namespace rtype::client::systems
