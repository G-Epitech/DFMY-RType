/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** game.cpp
*/

#include "game.hpp"

#include "client/src/components/server_entity_id.hpp"
#include "client/src/systems/background.hpp"
#include "client/src/systems/game/sync.hpp"
#include "libs/mew/src/sets/drawable/drawable.hpp"
#include "libs/mew/src/sets/events/events.hpp"
#include "libs/zygarde/src/core/components/components.hpp"
#include "menu.hpp"

using namespace mew::sets::events;
using namespace mew::sets::drawable;
using namespace porygon;
using namespace rtype::client::scenes;
using namespace rtype::client::services;
using namespace rtype::client::components;
using namespace rtype::client::systems;
using namespace zygarde::core::types;
using namespace zygarde::core::components;

SceneGame::SceneGame(DependenciesHandler::Ptr services) : SceneBase(std::move(services)) {
  serverConnectionService_ = services_->GetOrThrow<ServerConnectionService>();

  registry_->RegisterComponent<Tags>();
  registry_->RegisterComponent<ServerEntityId>();

  registry_->AddSystem<GameSyncSystem>(serverConnectionService_);
  registry_->AddSystem<BackgroundSystem>();
  /*registry_->AddSystem<PlayerSystem>(context_);*/
}

void SceneGame::OnCreate() {
  LoadResources();
  // CreateControls();
}

void SceneGame::CreateControls() {
  auto keyboard_controller = registry_->SpawnEntity();

  auto keypress_handler = [this](const sf::Keyboard::Key key) { return OnKeyPress(key); };
  registry_->AddComponent<OnKeyPressed>(keyboard_controller, {.handler = keypress_handler});
}

void SceneGame::OnKeyPress(const sf::Keyboard::Key &key) {
  switch (key) {
    case sf::Keyboard::Key::Escape:
      return managers_.scenes->GoToScene<SceneMenu>();
    default:
      break;
  }
}

void SceneGame::LoadResources() {
  managers_.resources->LoadTexture("assets/sheets/player.png", "player");
  managers_.resources->LoadTexture("assets/sheets/enemy.png", "enemy");
}

void SceneGame::CreatePlayerEntity() {
  auto player = registry_->SpawnEntity();
  auto controls_handler = [this, player](const sf::Keyboard::Key key) {
    auto positions = registry_->GetComponents<Position>();
    auto entity_id = static_cast<std::size_t>(player);

    if ((*positions).size() <= entity_id)
      return;
    auto &position = (*positions)[entity_id];
    if (key == sf::Keyboard::Left) {
      (*position).point.x -= 10;
    } else if (key == sf::Keyboard::Right) {
      (*position).point.x += 10;
    } else if (key == sf::Keyboard::Up) {
      (*position).point.y -= 10;
    } else if (key == sf::Keyboard::Down) {
      (*position).point.y += 10;
    }
  };

  static const sf::IntRect base{0, 0, 33, 36};

  registry_->AddComponent<Drawable>(
      player, {
                  .drawable = Texture{.name = "enemy", .scale = 3, .rect = base},
              });
  registry_->AddComponent<Tags>(player, Tags({"player"}));
  registry_->AddComponent<OnKeyPressed>(player, {.handler = controls_handler});
  registry_->AddComponent<Position>(player, {Vector3f{100, 100, 0}});
}
