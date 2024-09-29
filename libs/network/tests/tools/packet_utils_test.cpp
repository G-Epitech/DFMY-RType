/*
** EPITECH PROJECT, 2024
** packet_utils_test.cpp
** File description:
** packet_utils_test class
*/

#include <gtest/gtest.h>
#include "tools/packet/packet_utils.hpp"
#include "tools/packet/packet_builder.hpp"

using namespace rtype::sdk::network;

TEST(PacketUtilsTest, ExportMessageTypeFromBitset) {
  tools::PacketBuilder builder;

  builder.SetMessageType(43);
  tools::Packet<char> packet = builder.Build('c');
  auto bitset = packet.GetBitset();

  unsigned messageType = tools::PacketUtils::ExportMessageTypeFromBitset(bitset);
  EXPECT_EQ(messageType, 43);
}
