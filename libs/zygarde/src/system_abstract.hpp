/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** asystem.hpp
*/

#pragma once

#include "./registry.hpp"
#include "./tools/zipper.hpp"
#include "libs/zygarde/src/api.hpp"

namespace zygarde {
/**
 * @brief Abstract class for a system
 * @tparam Components Components to use in the system
 */
template <class... Components>
class EXPORT_ZYGARDE_API ASystem : public ISystem {
 public:
  void operator()(std::shared_ptr<Registry> r) override;

  typedef zipper<Components...> ComponentsPtr;

  /**
   * @brief Run the system
   * @param r The registry
   * @param components The components
   */
  virtual void Run(std::shared_ptr<Registry> r, ComponentsPtr components) = 0;
};

/**
 * Specialization for no components
 */
template <>
class EXPORT_ZYGARDE_API ASystem<> : public ISystem {
 public:
  void operator()(std::shared_ptr<Registry> r) override;

  virtual void Run(std::shared_ptr<Registry> r) = 0;
};
}  // namespace zygarde

#include "./system_abstract.tpp"
