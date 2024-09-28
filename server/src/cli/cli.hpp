/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options.hpp
*/

#pragma once

#include <boost/program_options.hpp>

#include "handlers/cli_handlers.hpp"
#include "src/server_types.hpp"

namespace po = boost::program_options;

namespace rtype::server {

using CliHandler = std::unique_ptr<ICliHandler>;

class Cli {
 public:
  Cli() = delete;
  ~Cli() = delete;

  static CliResult Run(int ac, char **av);

 private:
  static void Usage() noexcept;

  static CliHandler GetHandler(const std::string &serverTypeArg) noexcept;
};
}  // namespace rtype::server
