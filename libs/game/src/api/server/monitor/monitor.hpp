/*
** EPITECH PROJECT, 2024
** monitor.hpp
** File description:
** Monitor class
*/

#pragma once

#include "libs/abra/includes/network.hpp"
#include "libs/abra/src/tools/logger/logger.hpp"
#include "libs/game/src/api/props/network.hpp"
#include "libs/game/src/core.hpp"

namespace rtype::sdk::game::api {
class EXPORT_GAME_SDK_API Monitor;
}

class rtype::sdk::game::api::Monitor {
 public:
  /**
   * @brief Construct a new Monitor websocket object
   */
  Monitor();

  /**
   * @brief Destroy the Monitor object
   */
  ~Monitor();

  /**
   * @brief Handle a message
   * @param message The message
   */
  void MessageHandler(const std::pair<std::uint64_t, const boost::json::object &> &message);

 private:
  /// @brief The websocket server
  abra::server::ServerWebsocket ws_;

  /// @brief Thread of the server
  std::thread websocketThread_;

  /// @brief The logger
  abra::tools::Logger logger_;
};
