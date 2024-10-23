/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** handler.cpp
*/

#include "./handler.hpp"

using namespace porygon;

DependenciesHandler::DependenciesHandler(DependenciesHandler::Private)
    : std::enable_shared_from_this<DependenciesHandler>() {}

DependenciesHandler::Ptr DependenciesHandler::Create() {
  return std::make_shared<DependenciesHandler>();
}

DependenciesHandler::Ptr DependenciesHandler::GetShared() {
  return shared_from_this();
}
