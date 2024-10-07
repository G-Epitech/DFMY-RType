/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** asystem.hpp
*/

#pragma once

#include "system_abstract.hpp"

using namespace zygarde::ECS;

template <class... Components>
void ASystem<Components...>::operator()(std::shared_ptr<Registry> r) {
  Run(r, r->GetComponents<Components>()...);
}
