/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** asystem.hpp
*/

#pragma once

#include "registry.hpp"

namespace zygarde {

/**
 * @brief Abstract class for a system
 * @tparam Components Components to use in the system
 */
template <class... Components>
class EXPORT_ZYGARDE_API ASystem : public ISystem {
 public:
  void operator()(std::shared_ptr<Registry> r) override;

  /**
   * @brief Run the system
   * @param r The registry
   * @param components The components
   */
  virtual void Run(std::shared_ptr<Registry> r, sparse_array<Components> &...components) = 0;
};
}  // namespace zygarde

#include "system_abstract.tpp"
