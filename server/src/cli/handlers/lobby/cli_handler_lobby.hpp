/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_game.hpp
*/

#pragma once

#include "src/cli/handlers/abstract/cli_handler_abstract.hpp"
#include "src/context.hpp"

namespace rtype::server {

const std::size_t kDefaultTicks = 60;

class CliHandlerLobby : public CliHandlerAbstract {
 public:
  CliHandlerLobby();

  CliResult Run(int ac, char **av) override;

 private:
  void Setup() noexcept;

  BaseContext BuildCtx();
};
}  // namespace rtype::server::cli
