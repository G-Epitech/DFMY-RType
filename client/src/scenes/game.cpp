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

SceneGame::SceneGame(const GlobalContext& context) : SceneBase(context) {
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
}

void SceneGame::CreateControls() {
  auto keyboard_controller = registry_->SpawnEntity();

  auto keypress_handler = [this](const sf::Keyboard::Key key) { return OnKeyPress(key); };
  registry_->AddComponent<components::OnKeyPressed>(keyboard_controller,
                                                    {.handler = keypress_handler});
}

void SceneGame::OnKeyPress(const sf::Keyboard::Key& key) {
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
