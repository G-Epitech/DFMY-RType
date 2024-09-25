/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main.cpp
*/

#include "src/options/options.hpp"

int main(int ac, char **av) {
  rtype::server::cli::Options options;

  options.Parse(ac, av);
  return 0;
}
