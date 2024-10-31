/*
** EPITECH PROJECT, 2024
** master_test.cpp
** File description:
** master_test class
*/

#include <gtest/gtest.h>

#include "api/server/master/master.hpp"
#include "api/client/client.hpp"

using namespace rtype::sdk::game;

TEST(MasterTest, SimpleClientConnection) {
  api::Master master(40000, 50000);
  api::Client client(kLocalhost, 40000);

  payload::PlayerConnect playerConnect {
    .username = "user::test",
  };
  auto res = client.Register(playerConnect);
  EXPECT_EQ(res, true);

  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  auto queue = client.ExtractQueue();
  EXPECT_EQ(queue.size(), 2);

  auto &first = queue.front();
  if (first.messageType == MasterToClientMsgType::kMsgTypeMTCInfoGame) {
    auto gameInfo = client.ResolveGameInfo(first);
    EXPECT_EQ(gameInfo.nbUsers, 1);

    queue.pop();
  }
}
