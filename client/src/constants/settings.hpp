/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** settings.hpp
*/

#pragma once

#include "./game/keymap.hpp"

#define SETTING_APP_VOLUME "app:volume"
#define SETTING_GAME_ANIMATIONS "app:fullscreen"
#define SETTING_GAME_KEYMAP "game:keymap"
#define SETTING_APP_BLINDNESS_MODE "app:blindness_mode"

#define SETTING_DEFAULT_APP_VOLUME 100
#define SETTING_DEFAULT_GAME_ANIMATIONS true
#define SETTING_DEFAULT_GAME_KEYMAP rtype::client::KeyMap::ZQSD

#define SETTING_GAME_CHAT_OPEN "game:chat"
#define SETTING_PLAYER_USERNAME "player:username"
#define SETTING_PLAYER_USERNAME_MAX_LENGTH 20
#define SETTING_GAME_END_SCORE "game:end:score"
#define SETTING_GAME_END_WIN "game:end:win"
#define SETTING_GAME_END_TIME "game:end:time"

#define SETTING_DEFAULT_GAME_CHAT_OPEN false
#define SETTING_DEFAULT_PLAYER_USERNAME "Ptit'plouf"

#define SETTING_DEFAULT_GAME_END_SCORE 0
#define SETTING_DEFAULT_GAME_END_WIN false
#define SETTING_DEFAULT_GAME_END_TIME 0
