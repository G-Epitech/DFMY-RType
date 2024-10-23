/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** manager_base.cpp
*/

#include "./manager_base.hpp"

#include <utility>

using namespace mew::managers;

ManagerBase::ManagerBase(DependenciesHandler::Ptr services) : services_{std::move(services)} {}

ManagerBase::~ManagerBase() = default;
