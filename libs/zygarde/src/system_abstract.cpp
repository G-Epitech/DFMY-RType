/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** system_abstract.cpp
*/

#include "./system_abstract.hpp"

using namespace zygarde;

void Run(std::shared_ptr<Registry> r,
         zipper<typename sparse_array<Components>::ptr...> components) {}

void Run<>(std::shared_ptr<Registry> r) {}
