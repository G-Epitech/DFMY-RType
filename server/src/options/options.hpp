/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options.hpp
*/

#pragma once

#include <boost/program_options.hpp>

#include "handlers/option_handlers.hpp"
#include "src/server_types.hpp"

namespace po = boost::program_options;

namespace rtype::server::cli {
class Options {
 public:
  Options() = delete;
  ~Options() = delete;

  static CliResult Parse(int ac, char **av);

 private:
  static void Usage() noexcept;

  static std::unique_ptr<IOptionsHandler> AssignOptionsHandler(
      const std::string &serverTypeArg) noexcept;
};
}  // namespace rtype::server::cli
