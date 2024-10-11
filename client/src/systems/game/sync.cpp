/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** sync.cpp
*/

#include "sync.hpp"

#include <iostream>

using namespace rtype::client::systems;

void GameSyncSystem::Run(std::shared_ptr<Registry> r, sparse_array<int>::ptr component) {
  std::cout << "Syncing" << std::endl;
}
