/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_game.hpp
*/

#pragma once

#include "src/context.hpp"
#include "src/options/handlers/abstract/options_handler_abstract.hpp"

namespace rtype::server::cli {

const std::size_t kDefaultTicks = 60;

class OptionsHandlerLobby : public OptionsHandlerAbstract {
 public:
  OptionsHandlerLobby();

  CliResult Parse(int ac, char **av) override;

 private:
  void Setup() noexcept;

  BaseContext BuildCtx();
};
}  // namespace rtype::server::cli
