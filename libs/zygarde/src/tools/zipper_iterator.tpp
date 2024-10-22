/*
** EPITECH PROJECT, 2024
** rtype_bootstrap
** File description:
** zipper_iterator.tpp
*/

#pragma once

using namespace zygarde::tools;

template <class... Containers>
zygarde::tools::zipper_iterator<Containers...>::zipper_iterator(iterator_tuple const &it_tuple,
                                                                iterator_tuple const &end_tuple,
                                                                std::size_t max)
    : _current(it_tuple), _end(end_tuple), _max(max), _idx(0) {
  if (!all_set(_seq)) {
    ++(*this);
  }
}

template <class... Containers>
zygarde::tools::zipper_iterator<Containers...>::zipper_iterator(zipper_iterator const &z) = default;

template <class... Containers>
zygarde::tools::zipper_iterator<Containers...> &
zygarde::tools::zipper_iterator<Containers...>::operator++() {
  if (_current == _end) {
    return *this;
  }
  do {
    incr_all(_seq);
    ++_idx;
  } while (_idx < _max && !all_set(_seq));
  return *this;
}

template <class... Containers>
zygarde::tools::zipper_iterator<Containers...>
zygarde::tools::zipper_iterator<Containers...>::operator++(int) {
  zipper_iterator tmp = *this;
  ++(*this);
  return tmp;
}

template <class... Containers>
typename zygarde::tools::zipper_iterator<Containers...>::value_type
zygarde::tools::zipper_iterator<Containers...>::operator*() {
  return to_value(_seq);
}

template <class... Containers>
template <std::size_t... Is>
void zygarde::tools::zipper_iterator<Containers...>::incr_all(std::index_sequence<Is...>) {
  (++std::get<Is>(_current), ...);
}

template <class... Containers>
template <std::size_t... Is>
bool zygarde::tools::zipper_iterator<Containers...>::all_set(std::index_sequence<Is...>) {
  return (... &&
          (std::get<Is>(_current) != std::get<Is>(_end) && (*std::get<Is>(_current)).has_value()));
}

template <class... Containers>
template <std::size_t... Is>
typename zygarde::tools::zipper_iterator<Containers...>::value_type
zygarde::tools::zipper_iterator<Containers...>::to_value(std::index_sequence<Is...>) {
  return std::make_tuple(std::get<Is>(_current)->value()...);
}
