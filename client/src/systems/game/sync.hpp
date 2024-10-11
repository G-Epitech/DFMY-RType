/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** sync.hpp
*/

#pragma once

#include "libs/zygarde/src/system_abstract.hpp"

namespace rtype::client::systems {
class GameSyncSystem final : public ASystem<int> {
 public:
  GameSyncSystem() = default;
  ~GameSyncSystem() final = default;

  void Run(std::shared_ptr<Registry> r, sparse_array<int>::ptr component) final;
};
}  // namespace rtype::client::systems
