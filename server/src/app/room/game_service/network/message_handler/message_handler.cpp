/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** message_handler.cpp
*/

#include "message_handler.hpp"

#include "scripting/components/pool/script_pool.hpp"
#include "scripts/player_script.hpp"

using namespace rtype::server::game::network;

MessageHandler::MessageHandler() : packetBuilder_(), logger_("server-message-handler") {}

void MessageHandler::Run(const std::shared_ptr<zygarde::Registry>& registry,
                         const std::shared_ptr<rtype::sdk::game::api::Room>& api,
                         const std::map<std::uint64_t, PlayerProps>& players) {
  auto messages = api->ExtractQueue();

  while (!messages.empty()) {
    auto& [playerId, data] = messages.front();
    if (const auto player = players.find(playerId); player != players.end()) {
      HandlePlayerMessage(*player, data, registry);
    }
    messages.pop();
  }
}

void MessageHandler::HandlePlayerMessage(const std::pair<std::uint64_t, PlayerProps>& player,
                                         const abra::server::ClientUDPMessage& data,
                                         const std::shared_ptr<zygarde::Registry>& registry) {
  if (data.messageType == ClientToRoomMsgType::kMsgTypeCTRPlayerMove) {
    HandlePlayerMoveMessage(player, data, registry);
  }
  if (data.messageType == ClientToRoomMsgType::kMsgTypeCTRPlayerShoot) {
    HandlePlayerShootMessage(player, data, registry);
  }
}
void MessageHandler::HandlePlayerMoveMessage(const std::pair<std::uint64_t, PlayerProps>& player,
                                             const abra::server::ClientUDPMessage& data,
                                             const std::shared_ptr<zygarde::Registry>& registry) {
  auto playerId = player.first;

  try {
    const auto packet = packetBuilder_.Build<payload::Movement>(data.bitset);
    auto& [entityId, direction] = packet->GetPayload();

    const auto& playerEntity = player.second.entity;
    auto scriptPool = registry->GetComponent<scripting::components::ScriptPool>(playerEntity);
    if (!scriptPool) {
      return;
    }
    auto playerScript = (*scriptPool)->GetScript<scripts::PlayerScript>();
    if (playerScript) {
      playerScript->SetMovementDirection({direction.x, direction.y});
    }
  } catch (const std::exception& e) {
    logger_.Error("Error while handling player move: " + std::string(e.what()), "❌");
    return;
  }
}

void MessageHandler::HandlePlayerShootMessage(const std::pair<std::uint64_t, PlayerProps>& player,
                                              const abra::server::ClientUDPMessage& data,
                                              const std::shared_ptr<zygarde::Registry>& registry) {
  const auto& playerEntity = player.second.entity;
  if (!registry->HasEntityAtIndex(static_cast<std::size_t>(playerEntity))) {
    return;
  }
  auto scriptPool = registry->GetComponent<scripting::components::ScriptPool>(playerEntity);
  if (!scriptPool.has_value() || !scriptPool.value()) {
    return;
  }
  auto playerScript = (*scriptPool)->GetScript<scripts::PlayerScript>();
  if (playerScript) {
    playerScript->Shoot();
  } else {
    logger_.Error("Player script not found");
  }
}
