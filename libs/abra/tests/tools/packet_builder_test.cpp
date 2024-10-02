/*
** EPITECH PROJECT, 2024
** packet_builder_test.cpp
** File description:
** packet_builder_test class
*/

#include "tools/packet/packet_builder.hpp"

#include <gtest/gtest.h>

using namespace abra;

TEST(PacketBuilderTest, BasicPacketCreation) {
  tools::PacketBuilder packetBuilder;
  unsigned int helloMessageType = 1;
  char helloMessage[] = "Hello World!";

  packetBuilder.SetPayloadType(tools::PayloadType::kCustom);
  packetBuilder.SetMessageType(helloMessageType);

  tools::Packet<char *> packet = packetBuilder.Build(helloMessage);

  EXPECT_EQ(packet.GetHeader().payloadType, static_cast<unsigned>(tools::PayloadType::kCustom));
  EXPECT_EQ(packet.GetMessage().messageType, helloMessageType);
  EXPECT_EQ(packet.GetPayload(), helloMessage);
}

TEST(PacketBuilderTest, PacketCreationWithTurn) {
  tools::PacketBuilder packetBuilder;
  unsigned int helloMessageType = 1;
  char helloMessage[] = "Hello World!";
  std::uint16_t turn = 10;

  packetBuilder.SetPayloadType(tools::PayloadType::kCustom);
  packetBuilder.SetMessageType(helloMessageType);
  packetBuilder.SetTurn(turn);

  tools::Packet<char *> packet = packetBuilder.Build(helloMessage);

  EXPECT_EQ(packet.GetHeader().payloadType, static_cast<unsigned>(tools::PayloadType::kCustom));
  EXPECT_EQ(packet.GetMessage().messageType, helloMessageType);
  EXPECT_EQ(packet.GetHeader().turnFlag, 1);
  EXPECT_EQ(packet.GetTurn().turn, turn);
  EXPECT_EQ(packet.GetPayload(), helloMessage);
}

TEST(PacketBuilderTest, MultiPacketCreation) {
  tools::PacketBuilder packetBuilder;
  std::vector<std::uint8_t> payloads = {1, 2, 3, 4, 5};

  std::vector<tools::Packet<std::uint8_t>> packets =
      packetBuilder.SetPayloadType(tools::PayloadType::kUint8)
          .SetMessageType(3)
          .Build<std::uint8_t>(payloads);

  EXPECT_EQ(packets.size(), payloads.size());
  for (size_t i = 0; i < payloads.size(); i++) {
    EXPECT_EQ(packets[i].GetHeader().payloadType,
              static_cast<unsigned>(tools::PayloadType::kUint8));
    EXPECT_EQ(packets[i].GetMessage().messageType, 3);
    EXPECT_EQ(packets[i].GetPayload(), payloads[i]);

    EXPECT_EQ(packets[i].GetHeader().offsetFlag, 1);
    EXPECT_EQ(packets[i].GetOffset().offset, i);
    if (i == payloads.size() - 1)
      EXPECT_EQ(packets[i].GetOffset().offsetFlag, 1);
    else
      EXPECT_EQ(packets[i].GetOffset().offsetFlag, 0);
  }
}
