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
  iterator_tuple begin_;
  /// @brief End iterator tuple
  iterator_tuple end_;
  /// @brief Size of the zipper
  std::size_t size_;
};
}  // namespace zygarde::tools

#include "./zipper.tpp"
