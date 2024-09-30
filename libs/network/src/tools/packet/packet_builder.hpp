/*
** EPITECH PROJECT, 2024
** packet_builder.hpp
** File description:
** PacketBuilder class
*/

#pragma once

#include <vector>

#include "api.hpp"
#include "packet.hpp"

namespace rtype::sdk::network::tools {
class EXPORT_NETWORK_SDK_API PacketBuilder;
}

class EXPORT_NETWORK_SDK_API rtype::sdk::network::tools::PacketBuilder {
 public:
  PacketBuilder();

  ~PacketBuilder();

  /**
   * @brief Packet builder exceptions class
   */
  class Exception : public std::exception {
   public:
    /**
     * @brief Create a new message when packet builder exception
     * @param message The message
     */
    explicit Exception(std::string message);

    /**
     * @brief Get the exception message
     * @return The exception message
     */
    [[nodiscard]] const char *what() const noexcept override;

   private:
    /// @brief The exception message
    std::string mMessage;
  };

  /**
   * @brief Reset the packet builder
   */
  void Reset();

  /**
   * @brief Set the type of the payload
   * @param payloadType The payload type
   */
  PacketBuilder &SetPayloadType(PayloadType payloadType);

  /**
   * @brief Set turn (It will enable turn flag)
   * @param turn The turn (max 65535)
   */
  PacketBuilder &SetTurn(std::uint16_t turn);

  /**
   * @brief Set the message type
   * @param messageId The message type
   * @warning The message type must be between 0 and 63.
   */
  PacketBuilder &SetMessageType(std::uint8_t messageType);

  /**
   * @brief Build a packet with the given payload and the properties set
   * @tparam T The payload type
   * @param payload The payload
   * @return The packet
   */
  template <typename T>
  Packet<T> Build(T payload);

  /**
   * @brief Build a multiples packets with the given payloads and the properties set
   * @tparam T The payload type
   * @param payloads The payloads
   * @return The packets
   */
  template <typename T>
  std::vector<Packet<T>> Build(std::vector<T> payloads);

  /**
   * @brief Build a packet from a bitset
   * @warning All intern properties is ignored
   * @tparam T The payload type
   * @param bitset The bitset
   * @return The packet
   */
  template <typename T>
  Packet<T> Build(const dynamic_bitset &bitset);

 private:
  /**
   * @brief Check if the value is valid for the bit size
   * @param value The value to check
   * @param bitSize The bit size
   * @return True if the value is valid, false otherwise
   */
  [[nodiscard]] static bool IsValidBitSize(unsigned value, std::uint8_t bitSize);

  /**
   * @brief Generate a new packet ID
   */
  std::uint32_t GeneratePacketId();

  /// @brief Packet header properties
  PacketHeaderProps mHeader;
  /// @brief Packet message properties
  PacketMessageProps mMessage;
  /// @brief Packet turn properties
  PacketTurnProps mTurn;
  /// @brief Packet ID increment
  std::uint32_t mPacketIdIncrement;
};

#include "packet_builder.tpp"
