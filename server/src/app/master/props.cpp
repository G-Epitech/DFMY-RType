/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** props.cpp
*/

#include "props.hpp"

#include <utility>

using namespace rtype::server;

MasterCtxProps::MasterCtxProps(std::string token, std::size_t nodePort, std::string dbHost,
                               std::string dbPort, std::string dbUsername, std::string dbPassword,
                               std::string dbName)
    : token(std::move(token)),
      nodePort(nodePort),
      dbHost(std::move(dbHost)),
      dbPort(std::move(dbPort)),
      dbUsername(std::move(dbUsername)),
      dbPassword(std::move(dbPassword)),
      dbName(std::move(dbName)) {}

MasterCtxProps::MasterCtxProps() : token(), nodePort(0) {}
