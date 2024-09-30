/*
** EPITECH PROJECT, 2024
** bitset_test.cpp
** File description:
** bitset_test class
*/

#include <gtest/gtest.h>
#include "tools/packet/packet_builder.hpp"

using namespace rtype::sdk::network;

TEST(BitsetTest, ConvertSimplePacketToBitset) {
  tools::PacketBuilder packetBuilder;
  char payload = 'a';

  packetBuilder.SetPayloadType(tools::PayloadType::kCharacter);
  packetBuilder.SetMessageType(1);

  tools::Packet packet = packetBuilder.Build<char>(payload);
  auto bitset = packet.GetBitset();

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
