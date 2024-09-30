/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** asystem.hpp
*/

#pragma once

#include "registry.hpp"

namespace rtype::sdk::ECS {

/**
 * @brief Abstract class for a system
 * @tparam Components Components to use in the system
 */
template <class... Components>
class EXPORT_ECS_SDK_API ASystem : public ISystem {
 public:
  void operator()(Registry *r) override { Run(r, r->GetComponents<Components>()...); }

  /**
   * @brief Run the system
   * @param r The registry
   * @param components The components
   */
  virtual void Run(Registry *r, sparse_array<Components> &...components) = 0;
};
}  // namespace rtype::sdk::ECS
