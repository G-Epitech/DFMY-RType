/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** blink.hpp
*/

#pragma once
#include <SFML/System/Clock.hpp>

#include "core/components/tags/tags.hpp"
#include "sets/drawable/components/components.hpp"
#include "system_abstract.hpp"

namespace rtype::client::systems {
class BlinkSystem final
    : public ASystem<zygarde::core::components::Tags, mew::sets::drawable::Drawable> {
 public:
  BlinkSystem();

  void Run(std::shared_ptr<Registry> r, ZippedComponents components) override;

 private:
  /// @brief The clock to correctly blink the entities
  sf::Clock clock_;
  /// @brief Map of entities to blink
  std::map<std::size_t, sf::Time> entities_;
  /// @brief Map of entier to not blink
  std::map<std::size_t, sf::Time> entitiesNotBlink_;
};
}  // namespace rtype::client::systems
