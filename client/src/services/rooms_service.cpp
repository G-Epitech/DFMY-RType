/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** room_service.cpp
*/

#include "rooms_service.hpp"

using namespace rtype::client::services;

RoomsService::RoomsService(const DependenciesHandler::Ptr& services) {
  serverConnectionService_ = services->GetOrThrow<ServerConnectionService>();
}

void RoomsService::Refresh() {
  if (!serverConnectionService_->Connected()) {
    return;
  }
  serverConnectionService_->client()->RefreshInfos(false, true);
}

void RoomsService::PollUpdate() {
  if (!serverConnectionService_->Connected()) {
    return;
  }
  std::optional<payload::InfoRooms> last_room_infos;

  auto queue = serverConnectionService_->client()->ExtractQueue();
  while (!queue.empty()) {
    auto& message = queue.front();
    if (message.messageType == MasterToClientMsgType::kMsgTypeMTCInfoRooms) {
      last_room_infos = serverConnectionService_->client()->ResolveInfoRooms(message);
    }
    queue.pop();
  }
  if (last_room_infos.has_value()) {
    UpdateFromInfos(last_room_infos.value());
  }
}

void RoomsService::UpdateFromInfos(const payload::InfoRooms& infos) {
  lastRefreshTime_ = std::chrono::system_clock::now();
  canCreateRoom_ = infos.canCreate;
  rooms_.clear();
  for (std::size_t i = 0; i < infos.nbRooms; i++) {
    auto& room = infos.rooms[i];
    rooms_[room.nodeId][room.roomId] = room;
  }
}

std::chrono::system_clock::time_point RoomsService::GetLastRefreshTime() const {
  return lastRefreshTime_;
}

RoomsService::RoomsMap RoomsService::GetRooms() const {
  return rooms_;
}
bool RoomsService::CanCreateRoom() const {
  return canCreateRoom_;
}
bool RoomsService::JoinRoom(RoomsService::NodeIdType node_id, RoomsService::RoomIdType room_id) {
  if (!serverConnectionService_->Connected()) {
    return false;
  }
  if (!rooms_.contains(node_id) || !rooms_[node_id].contains(room_id)) {
    return false;
  }
  return serverConnectionService_->client()->JoinRoom({
      .nodeId = node_id,
      .roomId = room_id,
  });
}
