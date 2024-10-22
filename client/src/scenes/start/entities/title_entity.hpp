/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** title_entity.hpp
*/

#pragma once

#include "libs/zygarde/src/core/types/vector/vector.hpp"
#include "libs/zygarde/src/entity.hpp"
#include "libs/zygarde/src/registry.hpp"

namespace rtype::client::scenes {

class TitleEntity : public Entity {
  friend class zygarde::Registry;

 public:
  explicit TitleEntity(const Entity &other);

 protected:
  explicit TitleEntity(std::size_t idx, std::shared_ptr<Registry> registry);

  void OnSpawn(const std::string &text, zygarde::core::types::Vector3f position,
               const std::string &fontName = "main", unsigned int characterSize = 40);
};
}  // namespace rtype::client::scenes
