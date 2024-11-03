/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main.cpp
*/

#include "client/src/scenes/game.hpp"
#include "game/builder.hpp"
#include "scenes/game.hpp"

using namespace mew::game;

#if (defined(_WIN32) && !defined(DEBUG))
  #include <windows.h>
  #define MAIN \
    WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
  #define MAIN main()
#endif

int MAIN {
  auto builder = GameBuilder();

  builder.WithWindowProperties({
      .title = "Best Game",
      .videoMode = {800, 800},
      .style = sf::Style::Default,
      .contextSettings = sf::ContextSettings(),
      .frameLimit = 60,
  });
  {
    auto game = builder.Build();

    game.managers.scenes->RegisterScene<SceneGame>();
    game.managers.scenes->GoToScene<SceneGame>();

    return game.Run();
  }
}
