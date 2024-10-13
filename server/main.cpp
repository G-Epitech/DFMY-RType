/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main.cpp
*/

#include "libs/game/includes/api.hpp"

using namespace rtype::sdk::game;

void Handler(std::uint64_t id) {
    std::cout << "New user with id: " << id << std::endl;
}

int main(int ac, char **av)
{
    auto server = api::Server(5001);

    server.CreateLobby("Prototype game", Handler);

    while (true) {
        // wait some seconds with std
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
