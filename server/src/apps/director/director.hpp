/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** director.hpp
*/

#pragma once

#include <cstddef>

#include "props.hpp"
#include "src/apps/context.hpp"
#include "src/apps/server_interface.hpp"

namespace rtype::server {

class Director final : public IServer {
 public:
  /**
   * @brief Construct a new Director object
   * @param ctx The server context
   */
  explicit Director(const BaseContext &ctx);

  ~Director() override = default;

  /**
   * Run the director server
   * @return The server exit code
   */
  int Run() override;

 private:
  /// @brief Director server context
  struct Context {
    std::string name;        // Name of the server context
    std::size_t port;        // Port number
    ServerType type;         // Server type
    DirectorCtxProps props;  // Server type-specific properties
  };

 private:
  /// @brief Director server context
  Context mCtx;
};
}  // namespace rtype::server
