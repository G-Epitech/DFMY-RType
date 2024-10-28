/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_game.hpp
*/

#pragma once

#include "app/context.hpp"
#include "cli/handlers/abstract/cli_handler_abstract.hpp"

namespace rtype::server {
/// @brief Default server name
const char kDefaultName[] = "R-Type Lobby";

/// @brief Default number of ticks per second
const std::size_t kDefaultTicks = 60;

class CliHandlerLobby : public AbstractCliHandler {
 public:
  /**
   * @brief Construct a new CliHandlerLobby object and setup the cli options
   */
  CliHandlerLobby();

  /**
   * @brief Run the lobby server cli
   * @param ac number of arguments
   * @param av command line arguments
   * @return CliResult containing the server type and the server context
   */
  [[nodiscard]] CliResult Run(int ac, char **av) override;

 private:
  /**
   * @brief Setup the cli options
   */
  void Setup() noexcept;

  /**
   * @brief Build the server context from cli options
   * @return The server context
   */
  [[nodiscard]] BaseContext BuildCtx();
};
}  // namespace rtype::server
