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
    : begin_(std::make_tuple((*cs).begin()...)),
      end_(std::make_tuple((*cs).end()...)),
      size_(std::min({(*cs).size()...})) {}

template <class... Containers>
typename zygarde::tools::zipper<Containers...>::iterator
zygarde::tools::zipper<Containers...>::begin() {
  return iterator(begin_, end_, size_);
}

template <class... Containers>
typename zygarde::tools::zipper<Containers...>::iterator
zygarde::tools::zipper<Containers...>::end() {
  return iterator(end_, end_, size_);
}
