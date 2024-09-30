/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** app.hpp
*/

#pragma once

#include <memory>

#include "cli/handlers/cli_handlers.hpp"
#include "server_interface.hpp"

namespace rtype::server {
class App {
 public:
  App() = default;
  ~App() = default;

  /**
   * Start application using cli arguments
   * @param ac number of arguments
   * @param av command line arguments
   * @return status code
   */
  int Run(int ac, char **av);

 private:
  /**
   * Initialize server using cli arguments
   * @param cliResult cli result containing BaseContext needed for server
   * @return server instance
   */
  void InitializeServerInstance();

  /**
   * Parse cli arguments
   * @param ac number of arguments
   * @param av command line arguments
   * @return status code
   */
  int Cli(int ac, char **av);

 private:
  CliResult cliResult_;
  std::unique_ptr<IServer> server_;
};
}  // namespace rtype::server
