/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main.cpp
*/

#include "app/app.hpp"

using namespace rtype::server;

int main(int ac, char **av) {
  App app;

  return app.Run(ac, av);
}
