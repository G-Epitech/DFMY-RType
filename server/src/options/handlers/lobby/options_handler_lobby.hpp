/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_game.hpp
*/

#pragma once

#include "server/src/options/handlers/abstract/options_handler_abstract.hpp"

namespace rtype::server::cli {

const std::size_t kDefaultTicks = 60;

class OptionsHandlerLobby : public OptionsHandlerAbstract {
 public:
  OptionsHandlerLobby();

  void Parse(int ac, char **av) override;

 private:
  void Setup() noexcept;
};
}  // namespace rtype::server::cli
