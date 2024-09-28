/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_manager.hpp
*/

#pragma once

#include "src/apps/director/props.hpp"
#include "src/cli/handlers/abstract/cli_handler_abstract.hpp"

namespace rtype::server {
class CliHandlerDirector : public CliHandlerAbstract {
 public:
  CliHandlerDirector();

  CliResult Run(int ac, char **av) override;

 private:
  void Setup() noexcept;

  BaseContext BuildCtx();
};
}  // namespace rtype::server
