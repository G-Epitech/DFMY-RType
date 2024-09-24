/*
** EPITECH PROJECT, 2024
** packet.hpp
** File description:
** Packet class
*/

#pragma once

#include <exception>
#include <string>
#include "api.hpp"
#include "props/props.hpp"

namespace rtype::sdk::network::tools {
  template<typename T>
  class EXPORT_NETWORK_SDK_API Packet;
}

template<typename T>
class EXPORT_NETWORK_SDK_API rtype::sdk::network::tools::Packet {
public:
  /**
   * @brief Construct a new Packet object
   * @param header Header properties
   * @param message Message properties
   * @param payload Payload related to packet type
   * @param offset Offset properties (default: empty)
   * @param turn Turn properties (default: empty)
   */
  Packet(PacketHeaderProps header, PacketMessageProps message, T payload,
         PacketOffsetProps offset = PacketOffsetProps(),
         PacketTurnProps turn = PacketTurnProps());

  ~Packet();

  /**
   * @brief Packet exceptions class
   */
  class Exception : public std::exception {
  public:
    /**
     * @brief Create a new message when packet exception
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
   * @brief Check if the offset is enabled in the header
   * @return true if the offset flag is enabled (bit to 1)
   */
  [[nodiscard]] bool OffsetIsEnabled() const;

  /**
   * @brief Check if the turn is enabled in the header
   * @return true if the turn flag is enabled (bit to 1)
   */
  [[nodiscard]] bool TurnIsEnabled() const;

  /**
   * @brief Get the packet header properties
   * @return The packet header properties
   */
  [[nodiscard]] const PacketHeaderProps &GetHeader() const;

  /**
   * @brief Get the packet message properties
   * @return The packet message properties
   */
  [[nodiscard]] const PacketMessageProps &GetMessage() const;

  /**
   * @brief Get the packet offset properties
   * @return The packet offset properties
   */
  [[nodiscard]] const PacketOffsetProps &GetOffset() const;

  /**
   * @brief Get the packet turn properties
   * @return The packet turn properties
   */
  [[nodiscard]] const PacketTurnProps &GetTurn() const;

  /**
   * @brief Get the packet payload
   * @return The packet payload
   */
  [[nodiscard]] const T &GetPayload() const;

private:
  /// @brief Packet header properties
  PacketHeaderProps mHeader;
  /// @brief Packet message properties
  PacketMessageProps mMessage;
  /// @brief Packet offset properties
  PacketOffsetProps mOffset;
  /// @brief Packet turn properties
  PacketTurnProps mTurn;
  /// @brief Packet payload
  T mPayload;
};

#include "packet.tpp"
