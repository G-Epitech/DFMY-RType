/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** scenes.cpp
*/

#include "scenes.hpp"

#include "client/src/scenes/game.hpp"
#include "client/src/scenes/leaderboard.hpp"
#include "client/src/scenes/lobby.hpp"
#include "client/src/scenes/menu.hpp"
#include "client/src/scenes/register.hpp"
#include "client/src/scenes/settings.hpp"
#include "client/src/scenes/start/start.hpp"
#include "scenes/end.hpp"
#include "scenes/start/create_room.hpp"

using namespace rtype::client::builder;
using namespace rtype::client::scenes;

void Scenes::LoadScenes(mew::game::Game *game) {
  game->managers.scenes->RegisterScene<SceneRegister>();
  game->managers.scenes->RegisterScene<SceneMenu>();
  game->managers.scenes->RegisterScene<SceneSettings>();
  game->managers.scenes->RegisterScene<SceneLobby>();
  game->managers.scenes->RegisterScene<SceneGame>();
  game->managers.scenes->RegisterScene<SceneStart>();
  game->managers.scenes->RegisterScene<SceneCreateRoom>();
  game->managers.scenes->RegisterScene<SceneLeaderboard>();
  game->managers.scenes->RegisterScene<SceneEnd>();
}

void Scenes::SetEntryScene(mew::game::Game *game) {
  game->managers.scenes->GoToScene<SceneRegister>();
}
