/*
** EPITECH PROJECT, 2024
** rtype_bootstrap
** File description:
** zipper.hpp
*/

#pragma once

#include <cstddef>

#include "./spare_array.hpp"
#include "./zipper_iterator.hpp"

namespace zygarde::tools {
template <class... Containers>
class zipper {
 public:
  /// @brief Iterator type
  using iterator = zipper_iterator<typename sparse_array<Containers>::ptr...>;
  /// @brief Iterator tuple type
  using iterator_tuple = typename iterator::iterator_tuple;

  /**
   * @brief Construct a new zipper object
   * @param cs Containers
   */
  explicit zipper(sparse_array<Containers>::ptr &&...cs);

  /**
   * @brief Get the begin iterator
   * @return iterator
   */
  iterator begin();

  /**
   * @brief Get the end iterator
   * @return iterator
   */
  iterator end();

 private:
  /// @brief Dynamic begin function builder
  std::function<iterator_tuple()> dynamicBegin_;

  /// @brief Dynamic end function builder
  std::function<iterator_tuple()> dynamicEnd_;

  /// @brief Dynamic size function builder
  std::function<std::size_t()> dynamicSize_;
};
}  // namespace zygarde::tools

#include "./zipper.tpp"
