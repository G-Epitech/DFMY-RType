/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** TextureMapper.hpp
*/

#pragma once

#include "components/drawable.hpp"
#include "game/src/types/projectile.hpp"

namespace rtype::client::systems {
class TextureMapper final {
 public:
  TextureMapper() = delete;

  /**
   * Map bullet type to texture
   * @param type Type of the bullet
   * @return Texture component
   */
  static components::Texture MapBulletType(sdk::game::types::ProjectileType type) noexcept;
};
}  // namespace rtype::client::systems
