/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** asystem.hpp
*/

#pragma once

#include "system_abstract.hpp"

using namespace rtype::sdk::ECS;

template <class... Components>
void ASystem<Components...>::operator()(Registry *r) {
  Run(r, r->GetComponents<Components>()...);
}
