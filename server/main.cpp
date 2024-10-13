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

    std::cout << "Server started" << std::endl;

    auto client = api::Client("127.0.0.1", 5001);
}
