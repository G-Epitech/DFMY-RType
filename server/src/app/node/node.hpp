/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** master.hpp
*/

#pragma once

#include <boost/process.hpp>
#include <cstddef>

#include "libs/game/includes/api.hpp"
#include "server/src/app/context.hpp"
#include "server/src/app/node/props.hpp"
#include "server/src/app/server_interface.hpp"
#include "server/src/server_types.hpp"

namespace rtype::server {
class Node;
}

class rtype::server::Node final : public IServer {
 public:
  /**
   * @brief Construct a new Master object
   * @param ctx The server context
   */
  explicit Node(const BaseContext &ctx);

  ~Node();

  /**
   * Run the master server
   * @return The server exit code
   */
  int Run() override;

  /**
   * @brief Create a new room
   * @param roomId The room id
   * @param maxPlayers The maximum number of players
   * @param difficulty The difficulty of the room
   * @return True if the room was created, false otherwise
   */
  bool CreateNewRoom(std::uint64_t roomId, std::size_t maxPlayers, std::size_t difficulty, unsigned int port);

 private:
  /// @brief Master server context
  struct Context {
    /// @brief Name of the server
    std::string name;
    /// @brief Port number of the server
    std::size_t port;
    /// @brief Server type
    ServerType type;
    /// @brief Server type-specific properties
    NodeCtxProps props;
  };

  /// @brief Node server context
  Context ctx_;

  /// @brief List of children processes
  std::vector<boost::process::child> childrens_;

  /// @brief Server network
  rtype::sdk::game::api::Node api_;
};
