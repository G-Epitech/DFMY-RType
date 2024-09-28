/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_interface.hpp
*/

#pragma once

#include <optional>

#include "server/src/context.hpp"

namespace rtype::server::cli {

using CliResult = std::optional<BaseContext>;

class IOptionsHandler {
 public:
  virtual ~IOptionsHandler() = default;

  virtual CliResult Parse(int ac, char **av) = 0;
};
}  // namespace rtype::server::cli
