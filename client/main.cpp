/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main.cpp
*/

#include "app/app.hpp"

using namespace rtype::client;

#if (defined(_WIN32) && !defined(DEBUG))
  #define MAIN WinMain
#else
  #define MAIN main
#endif

int MAIN() {
  try {
    App app;

    app.Run();
    return 0;
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 84;
  }
}
