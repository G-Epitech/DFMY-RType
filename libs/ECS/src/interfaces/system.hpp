/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ISystem.hpp
*/

#pragma once

namespace rtype::sdk::ECS {

class Registry;

/**
 *  @brief Interface for a system
 */
class ISystem {
 public:
  virtual ~ISystem() = default;

  /**
   * @brief Run the system
   * @param r The registry
   */
  virtual void operator()(Registry *r) = 0;
};

}  // namespace rtype::sdk::ECS
