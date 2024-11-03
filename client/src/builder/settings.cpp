/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** settings.cpp
*/

#include "settings.hpp"

#include "client/src/constants/settings.hpp"

using namespace rtype::client::builder;

void Settings::LoadSettings(mew::game::Game *game) {
  game->managers.settings->Set(SETTING_APP_VOLUME, SETTING_DEFAULT_APP_VOLUME);
  game->managers.settings->Set(SETTING_GAME_KEYMAP, SETTING_DEFAULT_GAME_KEYMAP);
  game->managers.settings->Set(SETTING_GAME_ANIMATIONS, SETTING_DEFAULT_GAME_ANIMATIONS);
  game->managers.settings->Set(SETTING_GAME_CHAT_OPEN, SETTING_DEFAULT_GAME_CHAT_OPEN);
  game->managers.settings->Set(SETTING_PLAYER_USERNAME,
                               std::string(SETTING_DEFAULT_PLAYER_USERNAME));
}
