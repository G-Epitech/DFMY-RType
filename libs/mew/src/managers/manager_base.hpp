/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** manager_base.hpp
*/

#pragma once

#include "libs/mew/include/api.hpp"
#include "libs/porygon/src/handler.hpp"

namespace mew::managers {

using namespace porygon;

class EXPORT_MEW_API ManagerBase {
 public:
  /**
   * @brief Destroy the Manager Base object
   */
  ~ManagerBase();

 protected:
  /**
   * @brief Construct a new Manager Base object
   * @param services Managers provider
   */
  explicit ManagerBase(DependenciesHandler::Ptr services);

  /// @brief Store the managers provider
  DependenciesHandler::Ptr services_;
};
}  // namespace mew::managers
