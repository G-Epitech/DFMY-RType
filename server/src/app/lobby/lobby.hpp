/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** lobby.hpp
*/

#pragma once

#include <cstddef>

#include "app/context.hpp"
#include "app/server_interface.hpp"
#include "props.hpp"

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
    /// @brief Name of the server
    std::string name;
    /// @brief Port number of the server
    std::size_t port;
    /// @brief Server type
    ServerType type;
    /// @brief Server type-specific properties
    LobbyCtxProps props;
  };

 private:
  /// @brief Lobby server context
  Context ctx_;
};
}  // namespace rtype::server
