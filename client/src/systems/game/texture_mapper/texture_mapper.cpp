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
    case ::game::types::ProjectileType::kEnforcer: {
      return Texture{.name = "enemy_pack", .scale = 2, .rect = {412, 725, 32, 6}};
    }
    case ::game::types::ProjectileType::kVoidEater: {
      return Texture{.name = "enemy_pack", .scale = 2, .rect = {531, 225, 32, 32}};
    }
    default: {
      return Texture{.name = "player", .scale = 2, .rect = {227, 278, 10, 8}};
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
    case game::types::EnemyType::kEnforcer: {
      return Texture{.name = "enemy_pack", .scale = 2.5, .rect = {387, 821, 71, 61}};
    }
    case game::types::EnemyType::kElectricShark: {
      return Texture{.name = "enemy_pack", .scale = 1.5, .rect = {674, 260, 64, 22}};
    }
    case game::types::EnemyType::kVoidEater: {
      return Texture{.name = "void_eater", .scale = 2.5, .rect = {22, 24, 156, 186}};
    }
    default: {
      return Texture{.name = "enemy", .scale = 2.5, .rect = {5, 6, 21, 24}};
    }
  }
}
