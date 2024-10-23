/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** asystem.hpp
*/

#pragma once

using namespace zygarde;

template <class... Components>
void ASystem<Components...>::Run(std::shared_ptr<Registry> r,
                                 zipper<typename sparse_array<Components>::ptr...> components) {
  // Implémentation de Run avec des composants
}

template <class... Components>
void ASystem<Components...>::operator()(std::shared_ptr<Registry> r) {
  Run(r, zipper<typename sparse_array<Components>::ptr...>(r->GetComponents<Components>()...));
}

inline void ASystem<>::Run(std::shared_ptr<Registry> r) {
  // Spécialisation complète sans composants
}

inline void ASystem<>::operator()(std::shared_ptr<Registry> r) {
  Run(r);
}
