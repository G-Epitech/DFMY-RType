/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** TextureMapper.cpp
*/

#include "texture_mapper.hpp"

using namespace rtype::client::systems;
using namespace rtype::sdk;

rtype::client::components::Texture TextureMapper::MapBulletType(
    const sdk::game::types::ProjectileType type) noexcept {
  switch (type) {
    case game::types::ProjectileType::kPlayerCommon: {
      return components::Texture {
        .name = "player", .scale = 2, .rect = { 200, 120, 32, 15 }
      };
    }
    default: {
      return components::Texture {
        .name = "player", .scale = 2, .rect = { 265, 120, 32, 15 }
      };
    }
  }
}
