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
  /**
   * @brief Initialize variables map and options description
   */
  CliHandlerAbstract();

  ~CliHandlerAbstract() override = default;

 protected:
  /// @brief Variables map that contains the parsed options
  po::variables_map mVariablesMap;

  /// @brief Options description
  po::options_description mDescription;
};
}  // namespace rtype::server
