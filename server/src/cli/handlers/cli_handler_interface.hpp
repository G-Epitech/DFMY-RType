/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_interface.hpp
*/

#pragma once

#include <optional>

#include "src/apps/context.hpp"

namespace rtype::server {
/// @brief CliResult alias
using CliResult = std::optional<BaseContext>;

class ICliHandler {
 public:
  virtual ~ICliHandler() = default;

  /**
   * Run the cli handler
   * @param ac number of arguments
   * @param av command line arguments
   * @return CliResult containing the server type and the server context
   */
  virtual CliResult Run(int ac, char **av) = 0;
};
}  // namespace rtype::server
