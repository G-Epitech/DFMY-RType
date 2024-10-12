/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main.cpp
*/

#include "libs/game/includes/api.hpp"

using namespace rtype::sdk::game;

int main(int ac, char **av)
{
    auto server = api::Server(5001);

    server.CreateLobby("Prototype game");

    while (true) {
        // wait some seconds with std
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
