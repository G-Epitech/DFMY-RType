/*
** EPITECH PROJECT, 2024
** packet_builder.hpp
** File description:
** PacketBuilder class
*/

#pragma once

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

private:
  /**
   * @brief Check if the value is valid for the bit size
   * @param value The value to check
   * @param bitSize The bit size
   * @return True if the value is valid, false otherwise
   */
  [[nodiscard]] static bool IsValidBitSize(unsigned value, std::uint8_t bitSize);

  /// @brief Packet header properties
  PacketHeaderProps mHeader;
  /// @brief Packet message properties
  PacketMessageProps mMessage;
  /// @brief Packet offset properties
  PacketOffsetProps mOffset;
  /// @brief Packet turn properties
  PacketTurnProps mTurn;
};
