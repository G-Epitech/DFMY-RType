/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** services.cpp
*/

#include "services.hpp"

#include "client/src/services/rooms_service.hpp"
#include "client/src/services/server_connection_service.hpp"

using namespace rtype::client::builder;
using namespace rtype::client::services;

void Services::RegisterServices(mew::game::GameBuilder *builder) {
  builder->WithService<ServerConnectionService>("rtype.thismath.com", 4848);
  builder->WithService<RoomsService>();
}
