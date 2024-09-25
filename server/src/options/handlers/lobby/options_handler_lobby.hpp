/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_game.hpp
*/

#pragma once

#include "server/src/options/handlers/abstract/options_handler_abstract.hpp"

namespace rtype::server::cli {

class OptionsHandlerLobby : public OptionsHandlerAbstract {
 public:
  OptionsHandlerLobby();
  ~OptionsHandlerLobby();

  void Parse(int ac, char **av) override;
};
}  // namespace rtype::server::cli
