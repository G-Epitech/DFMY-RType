/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** zipper.tpp
*/

#pragma once

using namespace zygarde::tools;

template <class... Containers>
zygarde::tools::zipper<Containers...>::zipper(Containers &...cs)
    : _begin(std::make_tuple((*cs).begin()...)),
      _end(std::make_tuple((*cs).end()...)),
      _size(_compute_size(cs...)) {}

template <class... Containers>
typename zygarde::tools::zipper<Containers...>::iterator
zygarde::tools::zipper<Containers...>::begin() {
  return iterator(_begin, _end, _size);
}

template <class... Containers>
typename zygarde::tools::zipper<Containers...>::iterator
zygarde::tools::zipper<Containers...>::end() {
  return iterator(_end, _end, _size);
}

template <class... Containers>
std::size_t zygarde::tools::zipper<Containers...>::_compute_size(Containers &...containers) {
  return std::min({(*containers).size()...});
}
