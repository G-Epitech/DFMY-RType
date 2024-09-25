/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options.hpp
*/

#pragma once

#include <boost/program_options.hpp>

#include "args/option_arg_server_type.hpp"
#include "src/server_types.hpp"

namespace po = boost::program_options;

namespace rtype::server {
class Options {
 public:
  Options();
  ~Options() = default;

  void ParseArguments(int ac, char **av);

 private:
  void AddOptions() noexcept;

 private:
  po::variables_map mVariablesMap;
  po::options_description mDescription;
};
}  // namespace rtype::server
