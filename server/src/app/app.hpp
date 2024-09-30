/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** runner.hpp
*/

#pragma once

#include <memory>

#include "server_interface.hpp"
#include "src/cli/handlers/cli_handlers.hpp"

namespace rtype::server {
class App {
 public:
  App() = delete;
  ~App() = delete;

  /**
   * Start application using cli arguments
   * @param ac number of arguments
   * @param av command line arguments
   * @return status code
   */
  static int Run(int ac, char **av);

 private:
  /**
   * Initialize server using cli arguments
   * @param cliResult cli result containing BaseContext needed for server
   * @return server instance
   */
  static std::unique_ptr<IServer> InitializeServer(CliResult cliResult);
};
}  // namespace rtype::server
