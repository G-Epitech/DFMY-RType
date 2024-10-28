/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** props.cpp
*/

#include "props.hpp"

#include <utility>

using namespace rtype::server;

MasterCtxProps::MasterCtxProps(std::string token) : token(std::move(token)) {}

MasterCtxProps::MasterCtxProps() : token() {}
