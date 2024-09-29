/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_abstract.hpp
*/

#pragma once

#include <boost/program_options.hpp>

#include "src/cli/handlers/cli_handler_interface.hpp"

namespace po = boost::program_options;

namespace rtype::server {
class CliHandlerAbstract : public ICliHandler {
 public:
  CliHandlerAbstract();
  ~CliHandlerAbstract() override = default;

 protected:
  po::variables_map mVariablesMap;
  po::options_description mDescription;
};
}  // namespace rtype::server
