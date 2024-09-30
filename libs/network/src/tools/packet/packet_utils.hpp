/*
** EPITECH PROJECT, 2024
** packet_utils.hpp
** File description:
** PacketUtils class
*/

#pragma once

#include "api.hpp"
#include "tools/bitset/dynamic_bitset.hpp"

namespace rtype::sdk::network::tools {
class EXPORT_NETWORK_SDK_API PacketUtils;
}

class EXPORT_NETWORK_SDK_API rtype::sdk::network::tools::PacketUtils {
 public:
  /**
   * @brief Export message type from bitset
   * @param bitset The bitset (Compressed packet)
   * @return The message type
   */
  [[nodiscard]] static unsigned ExportMessageTypeFromBitset(
      const std::shared_ptr<dynamic_bitset> &bitset);

 private:
  PacketUtils() = default;

  ~PacketUtils() = default;
};
