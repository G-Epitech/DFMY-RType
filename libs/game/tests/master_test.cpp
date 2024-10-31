/*
** EPITECH PROJECT, 2024
** master_test.cpp
** File description:
** master_test class
*/

#include <gtest/gtest.h>

#include "api/server/master/master.hpp"
#include "api/server/node/node.hpp"
#include "api/server/room/room.hpp"
#include "api/client/client.hpp"

using namespace rtype::sdk::game;

void Register(api::Client &client) {
  std::this_thread::sleep_for(std::chrono::milliseconds(300));

  payload::PlayerConnect playerConnect {
          .username = "user::test",
  };
  auto res = client.Register(playerConnect);
  EXPECT_EQ(res, true);
}

bool CreateRoom(std::uint64_t roomId, std::size_t maxPlayers, std::size_t difficulty,
                unsigned int port, std::shared_ptr<api::Room> &room) {
  room = std::make_shared<api::Room>(port, nullptr, roomId);

  room->RegisterNewRoom();

  return true;
}

TEST(MasterTest, ClientRegister) {
  api::Master master(40000, 50000);
  api::Client client(kLocalhost, 40000);

  Register(client);

  std::this_thread::sleep_for(std::chrono::milliseconds(300));

  auto queue = client.ExtractQueue();
  EXPECT_EQ(queue.size(), 2);

  auto &message = queue.front();
  EXPECT_EQ(message.messageType, MasterToClientMsgType::kMsgTypeMTCInfoGame);
  auto gameInfo = client.ResolveGameInfo(message);
  EXPECT_EQ(gameInfo.nbUsers, 1);

  queue.pop();

  message = queue.front();
  EXPECT_EQ(message.messageType, MasterToClientMsgType::kMsgTypeMTCInfoRooms);
  auto roomsInfo = client.ResolveInfoRooms(message);
  EXPECT_EQ(roomsInfo.nbRooms, 0);
  EXPECT_EQ(roomsInfo.canCreate, false);
}
