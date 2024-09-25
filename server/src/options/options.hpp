/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options.hpp
*/

#pragma once

#include <boost/program_options.hpp>

#include "args/option_arg_server_type.hpp"
#include "handlers/option_handlers.hpp"
#include "src/server_types.hpp"

namespace po = boost::program_options;

namespace rtype::server::cli {
class Options {
 public:
  Options();
  ~Options() = default;

  void Parse(int ac, char **av);

 private:
  void Setup() noexcept;

  void AssignOptionsHandler(ServerType serverType) noexcept;

 private:
  po::variables_map mVariablesMap;
  po::options_description mDescription;
  std::unique_ptr<IOptionsHandler> mOptionHandler;
};
}  // namespace rtype::server::cli
