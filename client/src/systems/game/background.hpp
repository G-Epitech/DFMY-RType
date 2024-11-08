/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** background.hpp
*/

#pragma once

#include <SFML/System/Clock.hpp>

#include "core/components/position/position.hpp"
#include "core/components/tags/tags.hpp"
#include "system_abstract.hpp"

namespace rtype::client::systems {
class BackgroundSystem
    : public ASystem<zygarde::core::components::Tags, zygarde::core::components::Position> {
 public:
  BackgroundSystem();

  void Run(std::shared_ptr<Registry> r,
           zipper<zygarde::core::components::Tags, zygarde::core::components::Position> components)
      override;

 private:
  /// @brief The clock to animate stars
  sf::Clock clock_;
  /// @brief The number of stars
  std::size_t starsCount_;

  /**
   * @brief Spawn a star in the background
   * @param r The registry
   */
  static void SpawnStar(const std::shared_ptr<Registry>& r);
};
}  // namespace rtype::client::systems
