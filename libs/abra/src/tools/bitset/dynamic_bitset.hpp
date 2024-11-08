/*
** EPITECH PROJECT, 2024
** dynamic_bitset.hpp
** File description:
** dynamic_bitset class
*/

#pragma once

#include <cstdint>
#include <iostream>
#include <vector>

#include "libs/abra/src/core.hpp"

namespace abra::tools {
class EXPORT_NETWORK_SDK_API dynamic_bitset;
}

class EXPORT_NETWORK_SDK_API abra::tools::dynamic_bitset {
 public:
  /**
   * @brief Construct a new Dynamic Bitset object
   * @param size The size of the bitset (in bits)
   */
  explicit dynamic_bitset(std::size_t size);

  /**
   * @brief Construct a new Dynamic Bitset object from a vector
   * @param vector The vector (buffer of bytes)
   */
  explicit dynamic_bitset(const std::vector<char> &vector, std::size_t size);

  ~dynamic_bitset();

  /**
   * @brief Set a bit in the bitset
   * @param index The index of the bit to set
   * @param value The value to set
   */
  void Set(std::size_t index, bool value);

  /**
   * @brief Append multiple bits in the bitset
   * @param value The value to append
   * @param size The size of the value (in bits)
   * @param offset The offset to append the value
   */
  void Append(unsigned value, std::size_t size, std::size_t offset);

  /**
   * @brief Get a bit in the bitset
   * @param index The index of the bit to get
   * @return The value of the bit
   */
  [[nodiscard]] bool Get(std::size_t index) const;

  /**
   * @brief Fill value from bitset range
   * @param start The start of the range
   * @param end The end of the range
   * @param value The value to fill
   */
  void FillFromRange(std::size_t start, std::size_t end, unsigned *value) const;

  /**
   * @brief Get the size of the bitset
   * @return The size of the bitset (in bits)
   */
  [[nodiscard]] std::size_t GetSize() const;

  /**
   * @brief Get the bitset vector
   * @return The vector
   */
  [[nodiscard]] const std::vector<std::uint8_t> &GetVector() const;

 private:
  /// @brief The size of the bitset (in bits)
  std::size_t size_;
  /// @brief The bitset
  std::vector<std::uint8_t> bitset_;
};

EXPORT_NETWORK_SDK_API std::ostream &operator<<(std::ostream &os,
                                                const abra::tools::dynamic_bitset &bitset);
