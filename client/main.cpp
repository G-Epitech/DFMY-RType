/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main.cpp
*/

#include "./src/builder/resources.hpp"
#include "./src/builder/scenes.hpp"
#include "./src/builder/services.hpp"
#include "./src/builder/settings.hpp"
#include "./src/constants/window.hpp"
#include "./src/scenes/game.hpp"
#include "./src/scenes/leaderboard.hpp"
#include "./src/scenes/lobby.hpp"
#include "./src/scenes/menu.hpp"
#include "./src/scenes/settings.hpp"
#include "libs/mew/src/game/builder.hpp"
#include "libs/mew/src/game/game.hpp"
#include "scenes/end.hpp"

using namespace mew::game;
using namespace rtype::client::builder;

#if (defined(_WIN32) && !defined(DEBUG))
  #include <windows.h>
  #define MAIN \
    WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
  #define MAIN main()
#endif

int MAIN {
  auto builder = GameBuilder();

  Services::RegisterServices(&builder);
  builder.WithWindowProperties({
      .title = APP_WINDOW_TITLE,
      .videoMode = {APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT},
      .style = APP_WINDOW_STYLE,
      .contextSettings = sf::ContextSettings(),
      .frameLimit = APP_WINDOW_FRAME_LIMIT,
      .iconPath = APP_WINDOW_ICON,
  });
  {
    auto game = builder.Build();

    Settings::LoadSettings(&game);
    Resources::LoadResources(&game);
    Scenes::LoadScenes(&game);
    Scenes::SetEntryScene(&game);

    return game.Run();
  }
}
