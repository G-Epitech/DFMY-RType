/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** TextureMapper.cpp
*/

#include "texture_mapper.hpp"

using namespace mew::sets::drawable;
using namespace rtype::client::systems;
using namespace rtype::sdk;

Texture TextureMapper::MapBulletType(const sdk::game::types::ProjectileType type) noexcept {
  switch (type) {
    case game::types::ProjectileType::kPlayerCommon: {
      return Texture{.name = "player", .scale = 3, .rect = {249, 90, 16, 4}};
    }
    case ::game::types::ProjectileType::kGrappler: {
      return Texture{.name = "enemy_pack", .scale = 2, .rect = {42, 719, 53, 7}};
    }
    default: {
      return Texture{.name = "player", .scale = 1.5, .rect = {300, 121, 32, 10}};
    }
  }
}
mew::sets::drawable::Texture TextureMapper::MapEnemyType(game::types::EnemyType type) noexcept {
  switch (type) {
    case game::types::EnemyType::kPata: {
      return Texture{.name = "enemy", .scale = 2.5, .rect = {5, 6, 21, 24}};
    }
    case game::types::EnemyType::kPataBig: {
      return Texture{.name = "enemy", .scale = 3.5, .rect = {5, 6, 21, 24}};
    }
    case game::types::EnemyType::kGrappler: {
      return Texture{.name = "enemy_pack", .scale = 2, .rect = {78, 743, 64, 24}};
    }
    default: {
      return Texture{.name = "enemy", .scale = 2.5, .rect = {5, 6, 21, 24}};
    }
  }
}
