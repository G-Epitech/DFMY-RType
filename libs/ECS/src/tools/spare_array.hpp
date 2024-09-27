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
EXPORT_ECS_SDK_API class SparseArray {
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
  EXPORT_ECS_SDK_API SparseArray();

  /**
   * @brief Duplicate constructor
   */
  EXPORT_ECS_SDK_API SparseArray(SparseArray const &);

  /**
   * @brief Move constructor
   */
  EXPORT_ECS_SDK_API SparseArray(SparseArray &&) noexcept;

  /**
   * @brief Destructor
   */
  EXPORT_ECS_SDK_API ~SparseArray();

  /**
   * @brief Copy assignment operator
   */
  EXPORT_ECS_SDK_API SparseArray &operator=(SparseArray const &);

  /**
   * @brief Move assignment operator
   */
  EXPORT_ECS_SDK_API SparseArray &operator=(SparseArray &&) noexcept;

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
  EXPORT_ECS_SDK_API iterator Begin();

  /**
   * @brief Begin iterator const
   */
  EXPORT_ECS_SDK_API const_iterator Begin() const;

  /**
   * @brief Begin iterator const
   */
  EXPORT_ECS_SDK_API const_iterator Cbegin() const;

  /**
   * @brief End iterator
   */
  EXPORT_ECS_SDK_API iterator End();

  /**
   * @brief End iterator const
   */
  EXPORT_ECS_SDK_API const_iterator End() const;

  /**
   * @brief End iterator const
   */
  EXPORT_ECS_SDK_API const_iterator Cend() const;

  /**
   * @brief Get size
   */
  EXPORT_ECS_SDK_API size_type Size() const;

  /**
   * @brief Insert at a specific position on a const component
   */
  EXPORT_ECS_SDK_API reference_type InsertAt(size_type pos, Component const &);

  /**
   * @brief Insert at a specific position on a component
   */
  EXPORT_ECS_SDK_API reference_type InsertAt(size_type pos, Component &&);

  /**
   * @brief Emplace at a specific position
   */
  template <class... Params>
  EXPORT_ECS_SDK_API reference_type EmplaceAt(size_type pos, Params &&...);

  /**
   * @brief Erase a component at a specific position
   */
  EXPORT_ECS_SDK_API void Erase(size_type pos);

  /**
   * @brief Get index of a component
   */
  EXPORT_ECS_SDK_API size_type GetIndex(value_type const &) const;

  /**
   * @brief Resize the sparse array
   */
  EXPORT_ECS_SDK_API void Resize(size_type new_size);

 private:
  /// @brief data storage
  container_t data_;
};
}  // namespace rtype::sdk::ECS::tools

#include "spare_array.tpp"
