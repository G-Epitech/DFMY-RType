/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** game.cpp
*/

#include "game.hpp"

#include "components/drawable.hpp"
#include "components/on_event.hpp"
#include "menu.hpp"
#include "systems/drawable.hpp"
#include "systems/events/key.hpp"
#include "systems/events/mouse/buttons.hpp"
#include "systems/events/mouse/move.hpp"
#include "systems/game/sync.hpp"

using namespace rtype::client::scenes;
using namespace rtype::client::systems;
using namespace rtype::client::components;
using namespace zygarde::core::components;

SceneGame::SceneGame(const GlobalContext &context) : SceneBase(context) {
  registry_->RegisterComponent<Drawable>();
  registry_->RegisterComponent<Position>();
  registry_->RegisterComponent<OnKeyPressed>();
  registry_->RegisterComponent<OnKeyReleased>();
  registry_->RegisterComponent<OnMousePressed>();
  registry_->RegisterComponent<OnMouseReleased>();
  registry_->RegisterComponent<OnMouseMoved>();
  registry_->RegisterComponent<int>();

  registry_->AddSystem<KeyPressEventSystem>(context_.windowManager);
  registry_->AddSystem<KeyReleaseEventSystem>(context_.windowManager);
  registry_->AddSystem<MousePressEventSystem>(context_.windowManager);
  registry_->AddSystem<MouseReleaseEventSystem>(context_.windowManager);
  registry_->AddSystem<MouseMoveEventSystem>(context_.windowManager);
  registry_->AddSystem<DrawableSystem>(context_.windowManager, resourcesManager_);
  registry_->AddSystem<GameSyncSystem>();
}

void SceneGame::OnCreate() {
  LoadResources();
  CreateControls();
  CreatePlayerEntity();
}

void SceneGame::CreateControls() {
  auto keyboard_controller = registry_->SpawnEntity();

  auto keypress_handler = [this](const sf::Keyboard::Key key) { return OnKeyPress(key); };
  registry_->AddComponent<components::OnKeyPressed>(keyboard_controller,
                                                    {.handler = keypress_handler});
}

void SceneGame::OnKeyPress(const sf::Keyboard::Key &key) {
  std::cout << "Key pressed: " << key << std::endl;
  switch (key) {
    case sf::Keyboard::Key::Escape:
      return context_.scenesManager->GoToScene<SceneMenu>();
    default:
      break;
  }
}

void SceneGame::LoadResources() {
  resourcesManager_->LoadTexture("assets/sheets/player.png", "player");
}

void SceneGame::CreatePlayerEntity() {
  auto player = registry_->SpawnEntity();
  auto controls_handler = [this, player](const sf::Keyboard::Key key) {
    auto positions = registry_->GetComponents<Position>();
    auto entity_id = static_cast<std::size_t>(player);
    auto &position = (*positions)[entity_id];

    if (!position)
      return;
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

  static const sf::IntRect base{100, 0, 32, 16};
  auto point = zygarde::core::types::Vector3f(100, 100);
  auto aligns = Alignment{HorizontalAlign::kLeft, VerticalAlign::kTop};
  registry_->AddComponent<Drawable>(
      player, {
                  .drawable = Texture{.name = "player", .scale = 4, .rect = base},
              });
  registry_->AddComponent<Position>(player, {point, aligns});
  registry_->AddComponent<OnKeyPressed>(player, {.handler = controls_handler});
}
