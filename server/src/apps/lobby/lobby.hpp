/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** lobby.hpp
*/

#pragma once

#include <cstddef>

#include "props.hpp"
#include "src/apps/context.hpp"
#include "src/apps/server_interface.hpp"

namespace rtype::server {
class Lobby final : public IServer {
 public:
  /**
   * @brief Construct a new Lobby object
   * @param ctx The server context
   */
  explicit Lobby(const BaseContext& ctx);

  ~Lobby() override = default;

  /**
   * Run the lobby server
   * @return The server exit code
   */
  int Run() override;

 private:
  /// @brief Lobby server context
  struct Context {
    std::string name;     // Name of the server
    std::size_t port;     // Port number of the server
    ServerType type;      // Server type
    LobbyCtxProps props;  // Server type-specific properties
  };

 private:
  /// @brief Lobby server context
  Context mCtx;
};
}  // namespace rtype::server
