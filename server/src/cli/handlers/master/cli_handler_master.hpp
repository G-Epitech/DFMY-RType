/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_manager.hpp
*/

#pragma once

#include "app/master/props.hpp"
#include "cli/handlers/abstract/cli_handler_abstract.hpp"

namespace rtype::server {
class CliHandlerMaster : public AbstractCliHandler {
 public:
  /**
   * @brief Construct a new CliHandlerMaster object and setup the cli options
   */
  CliHandlerMaster();

  /**
   * Run the master server cli
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
