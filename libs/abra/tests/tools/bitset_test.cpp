/*
** EPITECH PROJECT, 2024
** bitset_test.cpp
** File description:
** bitset_test class
*/

#include <gtest/gtest.h>

#include "tools/packet/packet_builder.hpp"

using namespace abra;

TEST(BitsetTest, ConvertSimplePacketToBitset) {
  tools::PacketBuilder packetBuilder;
  char payload = 'a';

  packetBuilder.SetPayloadType(tools::PayloadType::kCharacter);
  packetBuilder.SetMessageType(1);

  auto packet = packetBuilder.Build<char>(payload);
  auto bitset = packet->GetBitset();

  EXPECT_EQ(bitset->GetSize(), 7 * 8); // header(2), message(4), payload(1)

  EXPECT_EQ(bitset->Get(0), 0); // Start header payload length
  EXPECT_EQ(bitset->Get(9), 1); // End header payload length

  EXPECT_EQ(bitset->Get(10), 0); // Start header payload type
  EXPECT_EQ(bitset->Get(13), 1); // End header payload type

  EXPECT_EQ(bitset->Get(14), 0); // Offset flag
  EXPECT_EQ(bitset->Get(15), 0); // Turn flag

  EXPECT_EQ(bitset->Get(36), 0); // Start message type
  EXPECT_EQ(bitset->Get(41), 1); // End message type
}

TEST(BitsetTest, ConvertBitsetToPacket) {
  tools::PacketBuilder packetBuilder;
  struct payloadStruct {
    std::uint8_t a;
    std::uint16_t b;
    std::uint32_t c;
  } payload = {1, 2, 3};

  packetBuilder.SetPayloadType(tools::PayloadType::kCustom);
  packetBuilder.SetMessageType(42);

  auto packet = packetBuilder.Build<payloadStruct>(payload);
  auto bitset = packet->GetBitset();

  auto convertedPacket = packetBuilder.Build<payloadStruct>(bitset);

  EXPECT_EQ(convertedPacket->GetHeader().payloadType, static_cast<unsigned>(tools::PayloadType::kCustom));
  EXPECT_EQ(convertedPacket->GetHeader().payloadLength, sizeof(payload));
  EXPECT_EQ(convertedPacket->GetHeader().offsetFlag, 0);
  EXPECT_EQ(convertedPacket->GetHeader().turnFlag, 0);

  EXPECT_EQ(convertedPacket->GetMessage().messageType, 42);

  auto convertedPayload = convertedPacket->GetPayload();
  EXPECT_EQ(convertedPayload.a, payload.a);
  EXPECT_EQ(convertedPayload.b, payload.b);
  EXPECT_EQ(convertedPayload.c, payload.c);
}

TEST(BitsetTest, SuspiciousPacket) {
  tools::PacketBuilder packetBuilder;
  struct payloadStruct {
    std::size_t id;
    struct {
      float x;
      float y;
    } position;
    std::size_t health;
  };

  packetBuilder.SetPayloadType(tools::PayloadType::kCustom);
  packetBuilder.SetMessageType(5);

  std::vector<struct payloadStruct> payload = {
      {1, {1.0f, 2.0f}, 100},
  };

  auto packet = packetBuilder.Build<payloadStruct>(payload);
  EXPECT_EQ(packet[0]->GetHeader().offsetFlag, 1);

  auto bitset = packet[0]->GetBitset();

  auto header = tools::PacketUtils::ExportHeaderFromBitset(bitset);
  EXPECT_EQ(header.offsetFlag, 1);

  auto convertedPacket = packetBuilder.Build<payloadStruct>(bitset);

  EXPECT_EQ(convertedPacket->GetHeader().payloadType, static_cast<unsigned>(tools::PayloadType::kCustom));
  EXPECT_EQ(convertedPacket->GetHeader().payloadLength, sizeof(payloadStruct));
  EXPECT_EQ(convertedPacket->GetHeader().offsetFlag, 1);
  EXPECT_EQ(convertedPacket->GetHeader().turnFlag, 0);

  EXPECT_EQ(convertedPacket->GetMessage().messageType, 5);

  auto convertedPayload = convertedPacket->GetPayload();
  EXPECT_EQ(convertedPayload.id, payload[0].id);
  EXPECT_EQ(convertedPayload.position.x, payload[0].position.x);
  EXPECT_EQ(convertedPayload.health, payload[0].health);
}
