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
class Runner {
 public:
  Runner() = delete;
  ~Runner() = delete;

  static int StartApp(int ac, char **av);

 private:
  static std::unique_ptr<IServer> InitializeServer(CliResult cliResult);
};
}  // namespace rtype::server
