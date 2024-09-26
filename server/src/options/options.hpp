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
  Options() = default;
  ~Options() = default;

  void Parse(int ac, char **av);

 private:
  static void Usage() noexcept;

  void AssignOptionsHandler(const std::string &serverTypeArg) noexcept;

 private:
  std::unique_ptr<IOptionsHandler> mOptionsHandler;
};
}  // namespace rtype::server::cli
