/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** type.hpp
*/

#pragma once

namespace rtype::sdk::game::api {
/// @brief Client >> Master message type
enum ClientToMasterMsgType {
  kMsgTypeCTMConnect,          ///< @brief Connect to the master
  kMsgTypeCTMRefreshInfos,     ///< @brief Refresh the master infos
  kMsgTypeCTMCreateRoom,       ///< @brief Create a room
  kMsgTypeCTMJoinRoom,         ///< @brief Join a room
  kMsgTypeCTMInfoConnectRoom,  ///< @brief Info to connect to a room (client udp)
};

/// @brief Master >> Client message type
enum MasterToClientMsgType {
  kMsgTypeMTCInfoGame,     ///< @brief Info about the game
  kMsgTypeMTCInfoRooms,    ///< @brief Info about the rooms
  kMsgTypeMTCInfoRoom,     ///< @brief Info about a room (connection)
  kMsgTypeMTCGameStarted,  ///< @brief Game started
  kMsgTypeMTCGameEnded,    ///< @brief Game ended
};

/// @brief Node >> Master message type
enum NodeToMasterMsgType {
  kMsgTypeNTMRegisterNode,     ///< @brief Register a new node
  kMsgTypeNTMRegisterNewRoom,  ///< @brief Register a new room
  kMsgTypeNTMRoomGameStarted,  ///< @brief A room game started
  kMsgTypeNTMRoomGameEnded,    ///< @brief A room game ended
};

/// @brief Master >> Node message type
enum MasterToNodeMsgType {
  kMsgTypeMTNCreateRoom,  ///< @brief Create a room
  kMsgTypeMTNPlayerJoin,  ///< @brief Player join a room
};

/// @brief Room >> Node message type
enum RoomToNodeMsgType {
  kMsgTypeRTNRegisterRoom,  ///< @brief Register a room
  kMsgTypeRTNGameStarted,   ///< @brief Game started
  kMsgTypeRTNGameEnded,     ///< @brief Game ended
};

/// @brief Node >> Room message type
enum NodeToRoomMsgType {
  kMsgTypeNTRPlayerJoin,  ///< @brief Player join a room
};

/// @brief Room >> Client message type
enum RoomToClientMsgType {
  kMsgTypeRTCPlayersState,  ///< @brief Players state
  kMsgTypeRTCEnemiesState,  ///< @brief Enemies state
  kMsgTypeRTCBulletsState,  ///< @brief Bullets state
};

/// @brief Client >> Room message type
enum ClientToRoomMsgType {
  kMsgTypeCTRPlayerMove,   ///< @brief Player move
  kMsgTypeCTRPlayerShoot,  ///< @brief Player shoot
};
}  // namespace rtype::sdk::game::api
