/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** zipper.tpp
*/

#pragma once

using namespace zygarde::tools;

template <class... Containers>
zygarde::tools::zipper<Containers...>::zipper(sparse_array<Containers>::ptr &&...cs) {
    dynamicBegin_ = [cs...]() { return std::make_tuple(cs->begin()...); };
    dynamicEnd_ = [cs...]() { return std::make_tuple(cs->end()...); };
    dynamicSize_ = [cs...]() { return std::min({cs->size()...}); };
}

template <class... Containers>
typename zygarde::tools::zipper<Containers...>::iterator
zygarde::tools::zipper<Containers...>::begin() {
  return iterator(dynamicBegin_(), dynamicEnd_(), dynamicSize_());
}

template <class... Containers>
typename zygarde::tools::zipper<Containers...>::iterator
zygarde::tools::zipper<Containers...>::end() {
    return iterator(dynamicEnd_(), dynamicEnd_(), dynamicSize_());
}
