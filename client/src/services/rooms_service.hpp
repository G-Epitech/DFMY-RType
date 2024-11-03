/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** room_service.hpp
*/

#pragma once

#include "libs/porygon/src/handler.hpp"
#include "server_connection_service.hpp"

namespace rtype::client::services {

using namespace porygon;
using namespace rtype::sdk::game::api;

class RoomsService final {
 public:
  /// @brief Pointer to the room service
  using Ptr = std::shared_ptr<RoomsService>;
  /// @brief NodeId type
  using NodeIdType = typeof(payload::RoomStatus::nodeId);
  /// @brief RoomId type
  using RoomIdType = typeof(payload::RoomStatus::roomId);
  /// @brief RoomStatus type
  using RoomStatusType = typeof(payload::RoomStatus);
  /// @brief Rooms map
  using RoomsMap = std::map<NodeIdType, std::map<RoomIdType, RoomStatusType>>;

  /**
   * @brief Construct a new Room Service object
   */
  explicit RoomsService(const DependenciesHandler::Ptr& services);

  /**
   * @brief Destroy the Room Service object
   */
  ~RoomsService() = default;

  /**
   * @brief Refresh
   */
  void Refresh();

  /**
   * @brief Get the rooms
   * @return Last rooms
   */
  [[nodiscard]] RoomsMap GetRooms() const;

  /**
   * @brief Can create room
   * @return Can create room
   */
  [[nodiscard]] bool CanCreateRoom() const;

  /**
   * @brief Get the last refresh time
   * @return Last refresh time
   */
  [[nodiscard]] std::chrono::system_clock::time_point GetLastRefreshTime() const;

  /**
   * @brief Extract if needed
   */
  void PollUpdate();

 private:
  /// @brief Pointer to the server connection service
  ServerConnectionService::Ptr serverConnectionService_;

  /// @brief Last refresh time
  std::chrono::system_clock::time_point lastRefreshTime_;

  /// @brief Rooms information's
  RoomsMap rooms_;

  /// @brief Can create room
  bool canCreateRoom_ = false;

  /**
   * @brief Update from infos
   * @param infos Infos to update from
   */
  void UpdateFromInfos(const payload::InfoRooms& infos);
};
}  // namespace rtype::client::services