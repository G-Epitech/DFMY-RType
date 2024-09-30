/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** master.hpp
*/

#pragma once

#include <cstddef>

#include "props.hpp"
#include "src/apps/context.hpp"
#include "src/apps/server_interface.hpp"

namespace rtype::server {

class Master final : public IServer {
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
    std::string name;        // Name of the server context
    std::size_t port;        // Port number
    ServerType type;         // Server type
    MasterCtxProps props;  // Server type-specific properties
  };

 private:
  /// @brief Master server context
  Context mCtx;
};
}  // namespace rtype::server
