/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ISystem.hpp
*/

#pragma once

#include "api.hpp"

namespace rtype::sdk::ECS {

class Registry;

/**
 *  @brief Interface for a system
 */
class EXPORT_ECS_SDK_API ISystem {
 public:
  virtual ~ISystem() = default;

  /**
   * @brief Run the system
   * @param r The registry
   */
  virtual void operator()(std::shared_ptr<Registry> r) = 0;
};

}  // namespace rtype::sdk::ECS
