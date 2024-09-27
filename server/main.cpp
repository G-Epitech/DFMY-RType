/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main.cpp
*/

#include <iostream>
#include "src/options/options.hpp"

int main(int ac, char **av) {
  try {
    rtype::server::cli::Options::Parse(ac, av);
  } catch (std::exception &exception) {
    std::cerr << exception.what();
  }
  return 0;
}
