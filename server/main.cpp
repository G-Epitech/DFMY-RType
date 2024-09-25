/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main.cpp
*/

#include <iostream>
#include "src/options/options.hpp"

int main(int ac, char **av) {
  rtype::server::Options options;

  options.ParseArguments(ac, av);
  return 0;
}
