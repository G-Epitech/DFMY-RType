/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main.cpp
*/

#include "app/app.hpp"

using namespace rtype::client;

#ifdef _WIN32
  #define MAIN WinMain
#else
  #define MAIN main
#endif

int MAIN() {
  App app;

  app.Run();
  return 0;
}
