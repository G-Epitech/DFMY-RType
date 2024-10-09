/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** menu.cpp
*/

#include "menu.hpp"

using namespace rtype::client;

SceneMenu::SceneMenu(const GlobalContext& context) : SceneBase(context) {
  resourcesManager_.LoadFont("assets/fonts/main.ttf", "main");
}

void SceneMenu::OnActivate() {}

void SceneMenu::OnCreate() {}

void SceneMenu::Update(std::chrono::nanoseconds delta_time) {}
