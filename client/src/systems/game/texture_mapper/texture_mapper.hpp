/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** TextureMapper.hpp
*/

#pragma once

#include "game/src/types/projectile.hpp"
#include "libs/game/src/types/enemies.hpp"
#include "libs/mew/src/sets/drawable/drawable.hpp"

namespace rtype::client::systems {
class TextureMapper final {
 public:
  TextureMapper() = delete;

  /**
   * Map bullet type to texture
   * @param type Type of the bullet
   * @return Texture component
   */
  static mew::sets::drawable::Texture MapBulletType(sdk::game::types::ProjectileType type) noexcept;

  /**
   * Map enemy type to texture
   * @param type Type of the enemy
   * @return Texture component
   */
  static mew::sets::drawable::Texture MapEnemyType(sdk::game::types::EnemyType type) noexcept;
};
}  // namespace rtype::client::systems
