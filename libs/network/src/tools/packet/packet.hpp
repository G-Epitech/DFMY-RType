/*
** EPITECH PROJECT, 2024
** packet.hpp
** File description:
** Packet class
*/

#pragma once

#include <exception>
#include <memory>
#include <string>

#include "api.hpp"
#include "props/props.hpp"
#include "tools/bitset/dynamic_bitset.hpp"

namespace rtype::sdk::network::tools {
template <typename T>
class EXPORT_NETWORK_SDK_API Packet;
}

template <typename T>
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
         PacketOffsetProps offset = PacketOffsetProps(), PacketTurnProps turn = PacketTurnProps());

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

  /**
   * @brief Get the packet payload as a bitset (compressed packet)
   * @return The packet payload as a bitset
   */
  [[nodiscard]] std::shared_ptr<dynamic_bitset> GetBitset() const;

 private:
  /**
   * @brief Append the packet header to a bitset
   * @param bitset The bitset to append the header
   * @param offset The offset to append the header
   */
  void AppendHeaderToBitset(const std::shared_ptr<dynamic_bitset> &bitset,
                            std::size_t *offset) const;

  /**
   * @brief Append the packet message to a bitset
   * @param bitset The bitset to append the message
   * @param offset The offset to append the message
   */
  void AppendMessageToBitset(const std::shared_ptr<dynamic_bitset> &bitset,
                             std::size_t *offset) const;

  /**
   * @brief Append the packet offset to a bitset
   * @param bitset The bitset to append the offset
   * @param offset The offset to append the offset
   */
  void AppendOffsetToBitset(const std::shared_ptr<dynamic_bitset> &bitset,
                            std::size_t *offset) const;

  /**
   * @brief Append the packet turn to a bitset
   * @param bitset The bitset to append the turn
   * @param offset The offset to append the turn
   */
  void AppendTurnToBitset(const std::shared_ptr<dynamic_bitset> &bitset, std::size_t *offset) const;

  /**
   * @brief Append the packet payload to a bitset
   * @param bitset The bitset to append the payload
   * @param offset The offset to append the payload
   */
  void AppendPayloadToBitset(const std::shared_ptr<dynamic_bitset> &bitset,
                             const std::size_t *offset) const;

  /// @brief Packet header properties
  PacketHeaderProps header_;
  /// @brief Packet message properties
  PacketMessageProps message_;
  /// @brief Packet offset properties
  PacketOffsetProps offset_;
  /// @brief Packet turn properties
  PacketTurnProps turn_;
  /// @brief Packet payload
  T payload_;
};

#include "packet.tpp"
