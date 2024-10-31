/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** props.cpp
*/

#include "props.hpp"

#include <utility>

using namespace rtype::server;

MasterCtxProps::MasterCtxProps(std::string token, std::size_t nodePort)
    : token(std::move(token)), nodePort(nodePort) {}

MasterCtxProps::MasterCtxProps() : token(), nodePort(0) {}
