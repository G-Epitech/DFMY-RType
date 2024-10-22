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
    : current_(it_tuple), end_(end_tuple), max_(max), idx_(0) {
  if (!all_set(seq_)) {
    ++(*this);
  }
}

template <class... Containers>
zygarde::tools::zipper_iterator<Containers...>::zipper_iterator(zipper_iterator const &z) = default;

template <class... Containers>
zygarde::tools::zipper_iterator<Containers...> &
zygarde::tools::zipper_iterator<Containers...>::operator++() {
  if (current_ == end_) {
    return *this;
  }
  do {
    incr_all(seq_);
    ++idx_;
  } while (idx_ < max_ && !all_set(seq_));
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
  return to_value(seq_);
}

template <class... Containers>
template <std::size_t... Is>
void zygarde::tools::zipper_iterator<Containers...>::incr_all(std::index_sequence<Is...>) {
  (++std::get<Is>(current_), ...);
}

template <class... Containers>
template <std::size_t... Is>
bool zygarde::tools::zipper_iterator<Containers...>::all_set(std::index_sequence<Is...>) {
  return (... &&
          (std::get<Is>(current_) != std::get<Is>(end_) && (*std::get<Is>(current_)).has_value()));
}

template <class... Containers>
template <std::size_t... Is>
typename zygarde::tools::zipper_iterator<Containers...>::value_type
zygarde::tools::zipper_iterator<Containers...>::to_value(std::index_sequence<Is...>) {
  return std::make_tuple(std::get<Is>(current_)->value()...);
}
