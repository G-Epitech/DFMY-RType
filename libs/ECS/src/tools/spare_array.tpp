/*
** EPITECH PROJECT, 2024
** rtype_bootstrap
** File description:
** sparse_array.cpp
*/

#pragma once

template <typename Component>
sparse_array<Component>::sparse_array() = default;

template <typename Component>
sparse_array<Component>::sparse_array(sparse_array const &other) {
  _data = other._data;
}

template <typename Component>
sparse_array<Component>::sparse_array(sparse_array &&other) noexcept {
  _data = std::move(other._data);
}

template <typename Component>
sparse_array<Component>::~sparse_array() = default;

template <typename Component>
sparse_array<Component> &sparse_array<Component>::operator=(sparse_array const &other) = default;

template <typename Component>
sparse_array<Component> &sparse_array<Component>::operator=(sparse_array &&other) noexcept {
  _data = std::move(other._data);
  return *this;
}

template <typename Component>
typename sparse_array<Component>::reference_type sparse_array<Component>::operator[](size_t idx) {
  return _data[idx];
}

template <typename Component>
typename sparse_array<Component>::const_reference_type sparse_array<Component>::operator[](
    size_t idx) const {
  return _data[idx];
}

template <typename Component>
typename sparse_array<Component>::iterator sparse_array<Component>::begin() {
  return _data.begin();
}

template <typename Component>
typename sparse_array<Component>::const_iterator sparse_array<Component>::begin() const {
  return _data.begin();
}

template <typename Component>
typename sparse_array<Component>::const_iterator sparse_array<Component>::cbegin() const {
  return _data.cbegin();
}

template <typename Component>
typename sparse_array<Component>::iterator sparse_array<Component>::end() {
  return _data.end();
}

template <typename Component>
typename sparse_array<Component>::const_iterator sparse_array<Component>::end() const {
  return _data.end();
}

template <typename Component>
typename sparse_array<Component>::const_iterator sparse_array<Component>::cend() const {
  return _data.cend();
}

template <typename Component>
typename sparse_array<Component>::size_type sparse_array<Component>::size() const {
  return _data.size();
}

template <typename Component>
typename sparse_array<Component>::reference_type sparse_array<Component>::insert_at(
    size_type pos, Component const &component) {
  this->erase(pos);
  _data.insert(_data.begin() + pos, component);
  return _data[pos];
}

template <typename Component>
typename sparse_array<Component>::reference_type sparse_array<Component>::insert_at(
    size_type pos, Component &&component) {
  _data.insert(_data.begin() + pos, std::move(component));
  return _data[pos];
}

template <typename Component>
template <class... Params>
typename sparse_array<Component>::reference_type sparse_array<Component>::emplace_at(
    size_type pos, Params &&...params) {
  using Allocator = typename std::vector<Component>::allocator_type;
  std::allocator<Component> allocator = _data.get_allocator();

  std::allocator_traits<Allocator>::destroy(allocator, &_data[pos]);

  std::allocator_traits<Allocator>::construct(allocator, &_data[pos],
                                              std::forward<Params>(params)...);

  return _data[pos];
}

template <typename Component>
void sparse_array<Component>::erase(size_type pos) {
  _data.erase(_data.begin() + pos);
}

template <typename Component>
typename sparse_array<Component>::size_type sparse_array<Component>::get_index(
    value_type const &component) const {
  for (size_type i = 0; i < _data.size(); i++) {
    if (_data[i] == component)
      return i;
  }
  return -1;
}

template <typename Component>
void sparse_array<Component>::resize(size_type new_size) {
  if (new_size > _data.size()) {
    _data.resize(new_size);
  }
}

template <typename Component>
void sparse_array<Component>::shrink_to_fit() {
  size_t new_size = 0;
  for (size_t i = 0; i < _data.size(); ++i) {
    if (_data[i].has_value()) {
      new_size = i + 1;
    }
  }

  if (new_size < _data.size()) {
    _data.resize(new_size);
  }
}
