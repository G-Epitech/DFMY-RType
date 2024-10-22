/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** services.cpp
*/

#include "services.hpp"

#include "client/src/services/server_connection_service.hpp"

using namespace rtype::client::builder;
using namespace rtype::client::services;

void Services::RegisterServices(mew::game::GameBuilder &builder) {
  builder.WithService<ServerConnectionService>("127.0.0.1", 4848);
}
