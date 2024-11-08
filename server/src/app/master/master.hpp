/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** master.hpp
*/

#pragma once

#include <cstddef>

#include "libs/game/includes/api.hpp"
#include "server/src/app/context.hpp"
#include "server/src/app/master/props.hpp"
#include "server/src/app/server_interface.hpp"

namespace rtype::server {
class Master;
}

class rtype::server::Master final : public IServer {
 public:
  /**
   * @brief Construct a new Master object
   * @param ctx The server context
   */
  explicit Master(const BaseContext &ctx);

  ~Master() override = default;

  /**
   * Run the master server
   * @return The server exit code
   */
  int Run() override;

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
    MasterCtxProps props;
  };

  /// @brief Master server context
  Context ctx_;

  /// @brief Server network
  rtype::sdk::game::api::Master api_;
};
