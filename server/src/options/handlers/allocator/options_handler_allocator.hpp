/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_manager.hpp
*/

#pragma once

#include "server/src/options/handlers/abstract/options_handler_abstract.hpp"

namespace rtype::server::cli {
class OptionsHandlerAllocator : public OptionsHandlerAbstract {
 public:
  OptionsHandlerAllocator();

  void Parse(int ac, char **av) override;

 private:
  void Setup() noexcept;
};
}  // namespace rtype::server::cli
