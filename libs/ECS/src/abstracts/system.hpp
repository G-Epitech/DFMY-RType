/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** asystem.hpp
*/

#pragma once

#include "../registry.hpp"

namespace rtype::sdk::ECS {

/**
 * @brief Abstract class for a system
 * @tparam Components Components to use in the system
 */
template <class... Components>
class ASystem : public ISystem {
 public:
  void operator()(Registry *r) override { Run(r, r->GetComponents<Components>()...); }

  /**
   * @brief Run the system
   * @param r The registry
   * @param components The components
   */
  virtual void Run(Registry *r, SparseArray<Components> &...components) = 0;
};
}  // namespace rtype::sdk::ECS
