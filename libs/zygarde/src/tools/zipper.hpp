/*
** EPITECH PROJECT, 2024
** rtype_bootstrap
** File description:
** zipper.hpp
*/

#pragma once

#include <cstddef>

#include "./zipper_iterator.hpp"

namespace zygarde::tools {
template <class... Containers>
class zipper {
 public:
  /// @brief Iterator type
  using iterator = zipper_iterator<Containers...>;
  /// @brief Iterator tuple type
  using iterator_tuple = typename iterator::iterator_tuple;

  /**
   * @brief Construct a new zipper object
   * @param cs Containers
   */
  explicit zipper(Containers &...cs);

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
  /// @brief Begin iterator tuple
  iterator_tuple _begin;
  /// @brief End iterator tuple
  iterator_tuple _end;
  /// @brief Size of the zipper
  std::size_t _size;
};
}  // namespace zygarde::tools

#include "./zipper.tpp"
