/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** context.cpp
*/

#include "context.hpp"

using namespace rtype::server;

BaseContext::BaseContext(std::string name, std::size_t port, ServerType type, CtxProps props)
    : name(std::move(name)), port(port), type(type), props(props) {}
