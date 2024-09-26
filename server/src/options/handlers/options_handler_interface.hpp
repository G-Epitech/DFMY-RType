/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_interface.hpp
*/

#pragma once

namespace rtype::server::cli {
class IOptionsHandler {
 public:
  virtual ~IOptionsHandler() = default;

  virtual void Parse(int ac, char **av) = 0;
};
}  // namespace rtype::server::cli
