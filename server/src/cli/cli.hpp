/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options.hpp
*/

#pragma once

#include <boost/program_options.hpp>

#include "handlers/cli_handlers.hpp"
#include "server_types.hpp"

namespace po = boost::program_options;

namespace rtype::server {
/// @brief CliHandler interface wrapper
using CliHandler = std::unique_ptr<InterfaceCliHandler>;

class Cli {
 public:
  Cli() = delete;

  ~Cli() = delete;

  /**
   * Run the server cli
   * @param ac number of arguments
   * @param av command line arguments
   * @return CliResult containing the server type and the server context
   */
  static CliResult Run(int ac, char **av);

 private:
  /**
   * @brief Show usage
   */
  static void Usage() noexcept;

  /**
   * @brief Get the handler for a stringified server type
   * @param serverTypeArg the stringified server type
   * @return The specific cli handler for the server type
   */
  static CliHandler GetHandler(const std::string &serverTypeArg);
};
}  // namespace rtype::server
