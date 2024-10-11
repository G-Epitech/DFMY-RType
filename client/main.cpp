/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main.cpp
*/

#include "libs/game/includes/api.hpp"

using namespace rtype::sdk::game;

int main() {
  auto client = api::Client("127.0.0.1", 5001);

  payload::Connection connectPayload = {
          .pseudo = "TekMath"
  };

  auto success = client.Connect(connectPayload);
  if (!success) {
    std::cerr << "💔 Failed to connect to server" << std::endl;
    return 1;
  }
}
