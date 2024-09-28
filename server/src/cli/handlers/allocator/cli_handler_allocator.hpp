/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_manager.hpp
*/

#pragma once

#include "src/allocator/props.hpp"
#include "src/cli/handlers/abstract/cli_handler_abstract.hpp"

namespace rtype::server {
class CliHandlerAllocator : public CliHandlerAbstract {
 public:
  CliHandlerAllocator();

  CliResult Run(int ac, char **av) override;

 private:
  void Setup() noexcept;

  BaseContext BuildCtx();
};
}  // namespace rtype::server
