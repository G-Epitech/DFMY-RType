/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main.cpp
*/

#include "app/app.hpp"

int main(const int ac, char **av) {
  rtype::server::App app;

  return app.Run(ac, av);
}
