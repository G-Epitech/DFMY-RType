/*
** EPITECH PROJECT, 2024
** rtype_bootstrap
** File description:
** zipper_iterator.hpp
*/

#pragma once

#include <cstddef>
#include <tuple>

namespace zygarde::tools {
template <class... Containers>
class zipper_iterator {
  /// @brief The iterator type of the container
  template <class Container>
  using iterator_t = typename std::decay_t<decltype(*std::declval<Container>())>::iterator;

  /// @brief The reference type of the iterator
  template <class Container>
  using it_reference_t = typename iterator_t<Container>::reference;

  /// @brief Struct used to get the unwrapped type of container
  template <typename T, typename = void>
  struct unwrapped {
    using type = T;  ///< The unwrapped type of the container
  };

  /// @brief Struct used to get the unwrapped type of container
  template <typename T>
  struct unwrapped<T, std::void_t<typename T::value_type>> {
    using type = typename T::value_type::value_type;  ///< The unwrapped type of the container
  };

  /// @brief Struct used to get the unwrapped type of a shared pointer container
  template <typename T>
  struct unwrapped<std::shared_ptr<T>> {
    using type =
        typename T::value_type::value_type;  ///< The unwrapped type of the shared pointer container
  };

  /// @brief The unwrapped type of the container
  template <class T>
  using unwrapped_t = typename unwrapped<T>::type;

  /// @brief Struct used to store the index and the value of the iterator
  template <typename T>
  struct indexed_value {
    std::size_t index;  ///< The index of the iterator
    T values;           ///< The value of the iterator
  };

 public:
  /// @brief The value type of the iterator
  using value_type = std::tuple<unwrapped_t<Containers>...>;
  /// @brief The value type with index of the iterator
  using value_type_with_index = indexed_value<value_type>;
  /// @brief The reference type of the iterator
  using reference = value_type;
  /// @brief The pointer type of the iterator
  using pointer = void;
  /// @brief The difference type of the iterator
  using difference_type = std::size_t;
  /// @brief The iterator category
  using iterator_category = std::input_iterator_tag;
  /// @brief The iterator tuple type
  using iterator_tuple = std::tuple<iterator_t<Containers>...>;

  /**
   * @brief Construct a new zipper iterator object
   * @param it_tuple The tuple of iterators
   * @param end_tuple The tuple of end iterators
   * @param max The maximum number of elements to iterate
   */
  zipper_iterator(iterator_tuple const &it_tuple, iterator_tuple const &end_tuple, std::size_t max);

  /**
   * @brief Construct a new zipper iterator object
   * @param z The zipper iterator to copy
   */
  zipper_iterator(zipper_iterator const &z);

  /**
   * @brief Increment the iterator
   * @return zipper_iterator& The incremented iterator
   */
  zipper_iterator &operator++();

  /**
   * @brief Increment the iterator
   * @return zipper_iterator The incremented iterator
   */
  zipper_iterator operator++(int);

  /**
   * @brief Get the value of the iterator
   * @return value_type The value of the iterator
   */
  value_type operator*();

  /**
   * @brief Get the index and the value of the iterator
   * @return value_type_with_index The value of the iterator with index
   */
  value_type_with_index operator~();

  /**
   * @brief Check if two iterators are equal
   * @param lhs The left iterator
   * @param rhs The right iterator
   * @return true If the iterators are equal
   * @return false If the iterators are not equal
   */
  // This function can't be in a separate tpp file because it's a friend function
  friend bool operator==(zipper_iterator const &lhs, zipper_iterator const &rhs) {
    return lhs.current_ == rhs.current_;
  }

  /**
   * @brief Check if two iterators are not equal
   * @param lhs The left iterator
   * @param rhs The right iterator
   * @return true If the iterators are not equal
   * @return false If the iterators are equal
   */
  // This function can't be in a separate tpp file because it's a friend function
  friend bool operator!=(zipper_iterator const &lhs, zipper_iterator const &rhs) {
    return !(lhs == rhs);
  }

 private:
  /// @brief The current iterator tuple
  iterator_tuple current_;
  /// @brief The end iterator tuple
  iterator_tuple end_;
  /// @brief The maximum number of elements to iterate
  std::size_t max_;
  /// @brief The current index
  std::size_t idx_;
  /// @brief The index sequence
  static constexpr auto seq_ = std::index_sequence_for<Containers...>{};

  /**
   * @brief Increment all iterators
   * @tparam Is The index sequence
   */
  template <std::size_t... Is>
  void incr_all(std::index_sequence<Is...>);

  /**
   * @brief Check if all iterators are set
   * @tparam Is The index sequence
   * @return true If all iterators are set
   * @return false If not all iterators are set
   */
  template <std::size_t... Is>
  bool all_set(std::index_sequence<Is...>);

  /**
   * @brief Convert the iterators to a value
   * @tparam Is The index sequence
   * @return value_type The value of the iterators
   */
  template <std::size_t... Is>
  value_type to_value(std::index_sequence<Is...>);
};
}  // namespace zygarde::tools

#include "./zipper_iterator.tpp"
