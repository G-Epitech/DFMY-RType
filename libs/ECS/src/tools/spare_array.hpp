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

namespace rtype::sdk::ECS::tools {

/**
 * @brief Sparse array class
 * This class is used to represent a sparse array
 * @tparam Component Component type
 */
template <typename Component>
EXPORT_ECS_SDK_API class sparse_array {
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

 public:
  /**
   * @brief Default constructor
   */
  EXPORT_ECS_SDK_API sparse_array();

  /**
   * @brief Duplicate constructor
   */
  EXPORT_ECS_SDK_API sparse_array(sparse_array const &);

  /**
   * @brief Move constructor
   */
  EXPORT_ECS_SDK_API sparse_array(sparse_array &&) noexcept;

  /**
   * @brief Destructor
   */
  EXPORT_ECS_SDK_API ~sparse_array();

  /**
   * @brief Copy assignment operator
   */
  EXPORT_ECS_SDK_API sparse_array &operator=(sparse_array const &);

  /**
   * @brief Move assignment operator
   */
  EXPORT_ECS_SDK_API sparse_array &operator=(sparse_array &&) noexcept;

  /**
   * @brief Operator []
   */
  EXPORT_ECS_SDK_API reference_type operator[](size_t idx);

  /**
   * @brief Operator [] const
   */
  EXPORT_ECS_SDK_API const_reference_type operator[](size_t idx) const;

  /**
   * @brief Begin iterator
   */
  EXPORT_ECS_SDK_API iterator begin();

  /**
   * @brief Begin iterator const
   */
  EXPORT_ECS_SDK_API const_iterator begin() const;

  /**
   * @brief Begin iterator const
   */
  EXPORT_ECS_SDK_API const_iterator cbegin() const;

  /**
   * @brief End iterator
   */
  EXPORT_ECS_SDK_API iterator end();

  /**
   * @brief End iterator const
   */
  EXPORT_ECS_SDK_API const_iterator end() const;

  /**
   * @brief End iterator const
   */
  EXPORT_ECS_SDK_API const_iterator cend() const;

  /**
   * @brief Get size
   */
  EXPORT_ECS_SDK_API size_type size() const;

  /**
   * @brief Insert at a specific position on a const component
   */
  EXPORT_ECS_SDK_API reference_type insert_at(size_type pos, Component const &);

  /**
   * @brief Insert at a specific position on a component
   */
  EXPORT_ECS_SDK_API reference_type insert_at(size_type pos, Component &&);

  /**
   * @brief Emplace at a specific position
   */
  template <class... Params>
  EXPORT_ECS_SDK_API reference_type emplace_at(size_type pos, Params &&...);

  /**
   * @brief Erase a component at a specific position
   */
  EXPORT_ECS_SDK_API void erase(size_type pos);

  /**
   * @brief Get index of a component
   */
  EXPORT_ECS_SDK_API size_type get_index(value_type const &) const;

  /**
   * @brief Resize the sparse array
   */
  EXPORT_ECS_SDK_API void resize(size_type new_size);

 private:
  /// @brief data storage
  container_t _data;
};
}  // namespace rtype::sdk::ECS::tools

#include "spare_array.tpp"
