/*
** EPITECH PROJECT, 2024
** packet_utils.hpp
** File description:
** PacketUtils class
*/

#pragma once

#include <memory>

#include "./props/props.hpp"
#include "libs/abra/src/core.hpp"
#include "libs/abra/src/tools/bitset/dynamic_bitset.hpp"

namespace abra::tools {
class EXPORT_NETWORK_SDK_API PacketUtils;
}

class EXPORT_NETWORK_SDK_API abra::tools::PacketUtils {
 public:
  /**
   * @brief Export message type from bitset
   * @param bitset The bitset (Compressed packet)
   * @return The message type
   */
  [[nodiscard]] static unsigned ExportMessageTypeFromBitset(
      const std::shared_ptr<dynamic_bitset> &bitset);

  /**
   * @brief Export message id from bitset
   * @param bitset The bitset (Compressed packet)
   * @return The message id
   */
  [[nodiscard]] static unsigned ExportMessageIdFromBitset(
      const std::shared_ptr<dynamic_bitset> &bitset);

  /**
   * @brief Export header from bitset
   * @param bitset The bitset (Compressed packet)
   * @return The header properties
   */
  [[nodiscard]] static PacketHeaderProps ExportHeaderFromBitset(
      const std::shared_ptr<dynamic_bitset> &bitset);

  /**
   * @brief Export offset from bitset
   * @warning Be careful to have an offset in the bitset
   * @param bitset The bitset (Compressed packet)
   * @return The offset properties
   */
  [[nodiscard]] static PacketOffsetProps ExportOffsetFromBitset(
      const std::shared_ptr<dynamic_bitset> &bitset);

 private:
  PacketUtils() = default;

  ~PacketUtils() = default;
};
