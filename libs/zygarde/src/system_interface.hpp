/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ISystem.hpp
*/

#pragma once

#include "libs/zygarde/src/api.hpp"

namespace zygarde {

class Registry;

/**
 *  @brief Interface for a system
 */
class EXPORT_ZYGARDE_API ISystem {
 public:
  virtual ~ISystem() = default;

  /**
   * @brief Run the system
   * @param r The registry
   */
  virtual void operator()(std::shared_ptr<Registry> r) = 0;
};

}  // namespace zygarde
