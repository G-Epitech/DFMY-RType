/*
** EPITECH PROJECT, 2024
** packet_test.cpp
** File description:
** packet_test class
*/

#include "tools/packet/packet.hpp"

#include <gtest/gtest.h>

using namespace rtype::sdk::network;

TEST(PacketTest, DefaultPacketCreation) {
  auto header = tools::PacketHeaderProps();
  auto message = tools::PacketMessageProps();
  header.payloadLength = sizeof(std::uint8_t);
  message.messageId = 100;

  tools::Packet<std::uint8_t> packet(header, message, 1);

  EXPECT_EQ(packet.GetHeader().payloadLength, 1);
  EXPECT_EQ(packet.GetMessage().messageId, 100);
  EXPECT_EQ(packet.GetPayload(), 1);
}

TEST(PacketTest, SetOffsetWithoutHeaderFlagThrowException) {
  auto header = tools::PacketHeaderProps();
  auto message = tools::PacketMessageProps();
  auto offset = tools::PacketOffsetProps();
  header.payloadLength = sizeof(std::uint8_t);
  header.offsetFlag = 0;
  message.messageId = 100;
  offset.offset = 200;

  EXPECT_THROW(tools::Packet<std::uint8_t>(header, message, 1, offset),
               tools::Packet<std::uint8_t>::Exception);
}

TEST(PacketTest, SetTurnWithoutHeaderFlagThrowException) {
  auto header = tools::PacketHeaderProps();
  auto message = tools::PacketMessageProps();
  auto offset = tools::PacketOffsetProps();
  auto turn = tools::PacketTurnProps();
  header.payloadLength = sizeof(std::uint8_t);
  header.turnFlag = 0;
  message.messageId = 100;
  turn.turn = 10;

  EXPECT_THROW(tools::Packet<std::uint8_t>(header, message, 1, offset, turn),
               tools::Packet<std::uint8_t>::Exception);
}
