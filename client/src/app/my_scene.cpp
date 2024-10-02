/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** my_scene.cpp
*/

#include "my_scene.hpp"

#include <iostream>
#include <utility>

using namespace rtype::client;

MyScene::MyScene() {
  std::cout << "MyScene is created" << std::endl;
}

void MyScene::InjectGlobalContext(GlobalContext::Ptr globalContext) {
  _globalContext = std::move(globalContext);
}

void MyScene::Draw() {
  std::cout << "MyScene::Draw" << std::endl;
}
