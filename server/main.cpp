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

int main(int ac, char **av) {
  auto server = api::Server(5001);

  server.CreateLobby("Prototype game", Handler);

  // wait
  std::this_thread::sleep_for(std::chrono::seconds(5));

  std::vector<payload::PlayerState> state = std::vector<payload::PlayerState>();
  for (int i = 0; i < 10; i++) {
    state.push_back(payload::PlayerState{
            .entityId = static_cast<size_t>(i),
            .position = utils::types::vector_2f{.x = 0, .y = 0},
            .health = 100,
    });
  }

  server.SendPlayersState(0, state);

  std::this_thread::sleep_for(std::chrono::seconds(5));
}
