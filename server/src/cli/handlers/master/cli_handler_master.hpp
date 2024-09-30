/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_manager.hpp
*/

#pragma once

#include "src/app/master/props.hpp"
#include "src/cli/handlers/abstract/cli_handler_abstract.hpp"

namespace rtype::server {
class CliHandlerMaster : public CliHandlerAbstract {
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
  CliResult Run(int ac, char **av) override;

 private:
  /**
   * @brief Setup the cli options
   */
  void Setup() noexcept;

  /**
   * @brief Build the server context from cli options
   * @return The server context
   */
  BaseContext BuildCtx();
};
}  // namespace rtype::server
