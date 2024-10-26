/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** asystem.hpp
*/

#pragma once

using namespace zygarde;

template <class... Components>
void ASystem<Components...>::operator()(std::shared_ptr<Registry> r) {
  Run(r, zipper<Components...>(r->GetComponents<Components>()...));
}

inline void ASystem<>::operator()(std::shared_ptr<Registry> r) {
  Run(r);
}
