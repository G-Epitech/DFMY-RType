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

using CliResult = std::optional<BaseContext>;

class ICliHandler {
 public:
  virtual ~ICliHandler() = default;

  virtual CliResult Run(int ac, char **av) = 0;
};
}  // namespace rtype::server
