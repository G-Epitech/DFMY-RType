/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main.cpp
*/

#include "src/apps/runner.hpp"

int main(int ac, char **av) {
  return rtype::server::Runner::StartApp(ac, av);
}
