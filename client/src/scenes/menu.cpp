/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** my_scene.cpp
*/

#include "menu.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

using namespace rtype::client;

SceneMenu::SceneMenu(const GlobalContext& context) : SceneBase(context) {
  resourcesManager_.LoadFont("assets/fonts/main.ttf", "main");
}

void SceneMenu::OnActivate() {}

void SceneMenu::OnCreate() {}

void SceneMenu::Update(std::chrono::nanoseconds delta_time) {}
