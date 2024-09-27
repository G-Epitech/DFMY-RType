/*
** EPITECH PROJECT, 2024
** rtype_bootstrap
** File description:
** sparse_array.cpp
*/

#pragma once

using namespace rtype::sdk::ECS::tools;

template <typename Component>
SparseArray<Component>::SparseArray() = default;

template <typename Component>
SparseArray<Component>::SparseArray(SparseArray const &other) {
  data_ = other.data_;
}

template <typename Component>
SparseArray<Component>::SparseArray(SparseArray &&other) noexcept {
  data_ = std::move(other.data_);
}

template <typename Component>
SparseArray<Component>::~SparseArray() = default;

template <typename Component>
SparseArray<Component> &SparseArray<Component>::operator=(SparseArray const &other) = default;

template <typename Component>
SparseArray<Component> &SparseArray<Component>::operator=(SparseArray &&other) noexcept {
  data_ = std::move(other.data_);
  return *this;
}

template <typename Component>
typename SparseArray<Component>::reference_type SparseArray<Component>::operator[](size_t idx) {
  return data_[idx];
}

template <typename Component>
typename SparseArray<Component>::const_reference_type SparseArray<Component>::operator[](
    size_t idx) const {
  return data_[idx];
}

template <typename Component>
typename SparseArray<Component>::iterator SparseArray<Component>::Begin() {
  return data_.begin();
}

template <typename Component>
typename SparseArray<Component>::const_iterator SparseArray<Component>::Begin() const {
  return data_.begin();
}

template <typename Component>
typename SparseArray<Component>::const_iterator SparseArray<Component>::Cbegin() const {
  return data_.cbegin();
}

template <typename Component>
typename SparseArray<Component>::iterator SparseArray<Component>::End() {
  return data_.end();
}

template <typename Component>
typename SparseArray<Component>::const_iterator SparseArray<Component>::End() const {
  return data_.end();
}

template <typename Component>
typename SparseArray<Component>::const_iterator SparseArray<Component>::Cend() const {
  return data_.cend();
}

template <typename Component>
typename SparseArray<Component>::size_type SparseArray<Component>::Size() const {
  return data_.size();
}

template <typename Component>
typename SparseArray<Component>::reference_type SparseArray<Component>::InsertAt(
    size_type pos, Component const &component) {
  this->Erase(pos);
  data_.insert(data_.begin() + pos, component);
  return data_[pos];
}

template <typename Component>
typename SparseArray<Component>::reference_type SparseArray<Component>::InsertAt(
    size_type pos, Component &&component) {
  data_.insert(data_.begin() + pos, std::move(component));
  return data_[pos];
}

template <typename Component>
template <class... Params>
typename SparseArray<Component>::reference_type SparseArray<Component>::EmplaceAt(
    size_type pos, Params &&...params) {
  using Allocator = typename std::vector<Component>::allocator_type;
  std::allocator<Component> allocator = data_.get_allocator();

  std::allocator_traits<Allocator>::destroy(allocator, &data_[pos]);

  std::allocator_traits<Allocator>::construct(allocator, &data_[pos],
                                              std::forward<Params>(params)...);

  return data_[pos];
}

template <typename Component>
void SparseArray<Component>::Erase(size_type pos) {
  data_.erase(data_.begin() + pos);
}

template <typename Component>
typename SparseArray<Component>::size_type SparseArray<Component>::GetIndex(
    value_type const &component) const {
  for (auto i = 0; i < data_.size(); i++) {
    if (data_[i] == component)
      return i;
  }
  return -1;
}

template <typename Component>
void SparseArray<Component>::Resize(size_type new_size) {
  if (new_size > data_.size()) {
    data_.resize(new_size);
  }
}
