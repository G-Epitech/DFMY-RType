/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_abstract.hpp
*/

#pragma once

#include <boost/program_options.hpp>

#include "cli/handlers/cli_handler_interface.hpp"

namespace po = boost::program_options;

namespace rtype::server {
class AbstractCliHandler : public InterfaceCliHandler {
 public:
  /**
   * @brief Initialize variables map and options description
   */
  AbstractCliHandler();

  ~AbstractCliHandler() override = default;

 protected:
  /// @brief Variables map that contains the parsed options
  po::variables_map variablesMap_;

  /// @brief Options description
  po::options_description optDescription_;
};
}  // namespace rtype::server
