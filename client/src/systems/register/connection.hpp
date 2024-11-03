/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** blink.hpp
*/

#pragma once
#include <SFML/System/Clock.hpp>

#include "core/components/tags/tags.hpp"
#include "services/server_connection_service.hpp"
#include "sets/drawable/components/components.hpp"
#include "system_abstract.hpp"

namespace rtype::client::systems {
class ConnectionSystem final : public ASystem<> {
 public:
  ConnectionSystem(services::ServerConnectionService::Ptr serverConnectionService,
                   mew::managers::ScenesManager::Ptr scenesManager);

  void Run(std::shared_ptr<Registry> r) override;

 private:
  /// @brief Server connection service
  services::ServerConnectionService::Ptr serverConnectionService_;
  /// @brief Scenes manager
  mew::managers::ScenesManager::Ptr scenesManager_;
};
}  // namespace rtype::client::systems
