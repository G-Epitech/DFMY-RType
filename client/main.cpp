/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main.cpp
*/

#include "./src/constants/settings.hpp"
#include "./src/constants/window.hpp"
#include "./src/scenes/game.hpp"
#include "./src/scenes/lobby.hpp"
#include "./src/scenes/menu.hpp"
#include "./src/scenes/settings.hpp"
#include "libs/mew/src/game/builder.hpp"
#include "libs/mew/src/game/game.hpp"

using namespace mew::game;
using namespace rtype::client::scenes;
using namespace rtype::client::services;

#if (defined(_WIN32) && !defined(DEBUG))
  #include <windows.h>
  #define MAIN \
    WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
  #define MAIN main()
#endif

int MAIN {
  auto builder = GameBuilder();
  auto game = builder
                  .WithWindowProperties({
                      .title = APP_WINDOW_TITLE,
                      .videoMode = {APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT},
                      .style = APP_WINDOW_STYLE,
                      .contextSettings = sf::ContextSettings(),
                      .frameLimit = APP_WINDOW_FRAME_LIMIT,
                      .iconPath = APP_WINDOW_ICON,
                  })
                  .WithService<ServerConnectionService>("127.0.0.1", 4848)
                  .Build();

  game.managers.settings->Set(SETTING_APP_VOLUME, SETTING_DEFAULT_APP_VOLUME);
  game.managers.settings->Set(SETTING_GAME_KEYMAP, SETTING_DEFAULT_GAME_KEYMAP);
  game.managers.settings->Set(SETTING_GAME_ANIMATIONS, SETTING_DEFAULT_GAME_ANIMATIONS);
  game.managers.settings->Set(SETTING_GAME_CHAT_OPEN, SETTING_DEFAULT_GAME_CHAT_OPEN);

  game.managers.resources->LoadFont("assets/fonts/main.ttf", "main");
  game.managers.resources->LoadTexture("assets/icons/R-Type.png", "g-epitech-logo");

  game.managers.resources->LoadShader("assets/shaders/protanopia.frag", "protanopia",
                                      sf::Shader::Fragment);
  game.managers.resources->LoadShader("assets/shaders/deuteranopia.frag", "deuteranopia",
                                      sf::Shader::Fragment);
  game.managers.resources->LoadShader("assets/shaders/tritanopia.frag", "tritanopia",
                                      sf::Shader::Fragment);

  game.managers.scenes->RegisterScene<SceneMenu>();
  game.managers.scenes->RegisterScene<SceneSettings>();
  game.managers.scenes->RegisterScene<SceneLobby>();
  game.managers.scenes->RegisterScene<SceneGame>();
  game.managers.scenes->GoToScene<SceneMenu>();

  return game.Run();
}
