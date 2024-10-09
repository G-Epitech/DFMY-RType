/*
** EPITECH PROJECT, 2024
** server.cpp
** File description:
** Server class
*/

#include "server.hpp"

using namespace rtype::sdk::game::api;

Server::Server(int port) : serverTCP_(port) {}

void Server::InitTCP() {
  this->threadTCP_ = std::thread(&Server::ListenTCP, this);
}

void Server::ListenTCP() {
  this->serverTCP_.Start();
}
