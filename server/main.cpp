/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main.cpp
*/

#include <iostream>
#include "app/app.hpp"

int main(int ac, char **av) {
  rtype::server::App app;

  std::cout << "Starting server" << std::endl;
  return app.Run(ac, av);
}
