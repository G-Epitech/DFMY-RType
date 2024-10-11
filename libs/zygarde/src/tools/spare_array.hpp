/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** spare_array.hpp
*/

#pragma once

#include <cstddef>
#include <optional>
#include <vector>
#include <memory>

#include "../api.hpp"

namespace zygarde::tools {

/**
 * @brief Sparse array class
 * This class is used to represent a sparse array
 * @tparam Component Component type
 */
template <typename Component>
class EXPORT_ZYGARDE_API sparse_array {
 public:
  /// @brief Type aliases
  using value_type = std::optional<Component>;

  /// @brief Reference type
  using reference_type = value_type &;

  /// @brief Const reference type
  using const_reference_type = value_type const &;

  /// @brief Container type
  using container_t = std::vector<value_type>;

  /// @brief Size type
  using size_type = typename container_t::size_type;

  /// @brief Iterator type
  using iterator = typename container_t::iterator;

  /// @brief Const iterator type
  using const_iterator = typename container_t::const_iterator;

  /// @brief Pointer type
  using ptr = typename std::shared_ptr<sparse_array<Component>>;

 public:
  /**
   * @brief Default constructor
   */
  sparse_array();

  /**
   * @brief Duplicate constructor
   */
  sparse_array(sparse_array const &);

  /**
   * @brief Move constructor
   */
  sparse_array(sparse_array &&) noexcept;

  /**
   * @brief Destructor
   */
  ~sparse_array();

  /**
   * @brief Copy assignment operator
   */
  sparse_array &operator=(sparse_array const &);

  /**
   * @brief Move assignment operator
   */
  sparse_array &operator=(sparse_array &&) noexcept;

  /**
   * @brief Operator []
   */
  reference_type operator[](size_t idx);

  /**
   * @brief Operator [] const
   */
  const_reference_type operator[](size_t idx) const;

  /**
   * @brief Begin iterator
   */
  iterator begin();

  /**
   * @brief Begin iterator const
   */
  const_iterator begin() const;

  /**
   * @brief Begin iterator const
   */
  const_iterator cbegin() const;

  /**
   * @brief End iterator
   */
  iterator end();

  /**
   * @brief End iterator const
   */
  const_iterator end() const;

  /**
   * @brief End iterator const
   */
  const_iterator cend() const;

  /**
   * @brief Get size
   */
  size_type size() const;

  /**
   * @brief Insert at a specific position on a const component
   */
  reference_type insertAt(size_type pos, Component const &);

  /**
   * @brief Insert at a specific position on a component
   */
  reference_type insertAt(size_type pos, Component &&);

  /**
   * @brief Emplace at a specific position
   */
  template <class... Params>
  reference_type emplaceAt(size_type pos, Params &&...);

  /**
   * @brief Erase a component at a specific position
   */
  void erase(size_type pos);

  /**
   * @brief Get index of a component
   */
  size_type getIndex(value_type const &) const;

  /**
   * @brief Resize the sparse array
   */
  void resize(size_type new_size);

 private:
  /// @brief data storage
  container_t data_;
};
}  // namespace zygarde::tools

#include "spare_array.tpp"
