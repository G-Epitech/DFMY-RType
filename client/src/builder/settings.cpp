/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** settings.cpp
*/

#include "settings.hpp"

#include "client/src/constants/settings.hpp"
#include "constants/chat.hpp"
#include "constants/game.hpp"
#include "constants/user.hpp"

using namespace rtype::client::builder;

void Settings::LoadSettings(mew::game::Game *game) {
  game->managers.settings->Set(SETTING_APP_VOLUME, SETTING_DEFAULT_APP_VOLUME);
  game->managers.settings->Set(SETTING_GAME_KEYMAP, SETTING_DEFAULT_GAME_KEYMAP);
  game->managers.settings->Set(SETTING_GAME_ANIMATIONS, SETTING_DEFAULT_GAME_ANIMATIONS);
  game->managers.settings->Set(CHAT_IS_OPEN, CHAT_DEFAULT_IS_OPEN);
  game->managers.settings->Set(PLAYER_USERNAME, std::string(PLAYER_DEFAULT_USERNAME));
  game->managers.settings->Set(GAME_END_SCORE, static_cast<std::size_t>(GAME_DEFAULT_END_SCORE));
  game->managers.settings->Set(GAME_END_WIN, GAME_DEFAULT_END_WIN);
  game->managers.settings->Set(GAME_END_TIME, static_cast<time_t>(GAME_DEFAULT_END_TIME));
}
