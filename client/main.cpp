/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main.cpp
*/

#include "libs/game/includes/api.hpp"

using namespace rtype::sdk::game;

int main() {
  auto client = new api::Client("127.0.0.1", 5001);

  client->Register(api::payload::Connection{.pseudo = "User1"});
  client->JoinLobby(api::payload::JoinLobby{.lobbyId = 0});

  delete client;
}

