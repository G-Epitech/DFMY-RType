/*
** EPITECH PROJECT, 2024
** rtype_bootstrap
** File description:
** sparse_array.cpp
*/

#pragma once

using namespace rtype::sdk::ECS::tools;

template <typename Component>
sparse_array<Component>::sparse_array() = default;

template <typename Component>
sparse_array<Component>::sparse_array(sparse_array const &other) {
  data_ = other.data_;
}

template <typename Component>
sparse_array<Component>::sparse_array(sparse_array &&other) noexcept {
  data_ = std::move(other.data_);
}

template <typename Component>
sparse_array<Component>::~sparse_array() = default;

template <typename Component>
sparse_array<Component> &sparse_array<Component>::operator=(sparse_array const &other) = default;

template <typename Component>
sparse_array<Component> &sparse_array<Component>::operator=(sparse_array &&other) noexcept {
  data_ = std::move(other.data_);
  return *this;
}

template <typename Component>
typename sparse_array<Component>::reference_type sparse_array<Component>::operator[](size_t idx) {
  return data_[idx];
}

template <typename Component>
typename sparse_array<Component>::const_reference_type sparse_array<Component>::operator[](
    size_t idx) const {
  return data_[idx];
}

template <typename Component>
typename sparse_array<Component>::iterator sparse_array<Component>::begin() {
  return data_.begin();
}

template <typename Component>
typename sparse_array<Component>::const_iterator sparse_array<Component>::begin() const {
  return data_.begin();
}

template <typename Component>
typename sparse_array<Component>::const_iterator sparse_array<Component>::cbegin() const {
  return data_.cbegin();
}

template <typename Component>
typename sparse_array<Component>::iterator sparse_array<Component>::end() {
  return data_.end();
}

template <typename Component>
typename sparse_array<Component>::const_iterator sparse_array<Component>::end() const {
  return data_.end();
}

template <typename Component>
typename sparse_array<Component>::const_iterator sparse_array<Component>::cend() const {
  return data_.cend();
}

template <typename Component>
typename sparse_array<Component>::size_type sparse_array<Component>::size() const {
  return data_.size();
}

template <typename Component>
typename sparse_array<Component>::reference_type sparse_array<Component>::insertAt(
    size_type pos, Component const &component) {
  this->Erase(pos);
  data_.insert(data_.begin() + pos, component);
  return data_[pos];
}

template <typename Component>
typename sparse_array<Component>::reference_type sparse_array<Component>::insertAt(
    size_type pos, Component &&component) {
  data_.insert(data_.begin() + pos, std::move(component));
  return data_[pos];
}

template <typename Component>
template <class... Params>
typename sparse_array<Component>::reference_type sparse_array<Component>::emplaceAt(
    size_type pos, Params &&...params) {
  using Allocator = typename std::vector<Component>::allocator_type;
  std::allocator<Component> allocator = data_.get_allocator();

  std::allocator_traits<Allocator>::destroy(allocator, &data_[pos]);

  std::allocator_traits<Allocator>::construct(allocator, &data_[pos],
                                              std::forward<Params>(params)...);

  return data_[pos];
}

template <typename Component>
void sparse_array<Component>::erase(size_type pos) {
  data_.erase(data_.begin() + pos);
}

template <typename Component>
typename sparse_array<Component>::size_type sparse_array<Component>::getIndex(
    value_type const &component) const {
  for (auto i = 0; i < data_.size(); i++) {
    if (data_[i] == component)
      return i;
  }
  return -1;
}

template <typename Component>
void sparse_array<Component>::resize(size_type new_size) {
  if (new_size > data_.size()) {
    data_.resize(new_size);
  }
}
