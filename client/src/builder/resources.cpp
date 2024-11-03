/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** resources.cpp
*/

#include "resources.hpp"

using namespace rtype::client::builder;

void Resources::LoadResources(mew::game::Game *game) {
  game->managers.resources->LoadFont("assets/fonts/main.ttf", "main");
  game->managers.resources->LoadTexture("assets/icons/R-Type.png", "g-epitech-logo");

  game->managers.resources->LoadShader("assets/shaders/protanopia.frag", "protanopia",
                                       sf::Shader::Fragment);
  game->managers.resources->LoadShader("assets/shaders/deuteranopia.frag", "deuteranopia",
                                       sf::Shader::Fragment);
  game->managers.resources->LoadShader("assets/shaders/tritanopia.frag", "tritanopia",
                                       sf::Shader::Fragment);
  game->managers.sound->LoadSoundBuffer("assets/sounds/button_click.ogg", "buttons:click");
}
