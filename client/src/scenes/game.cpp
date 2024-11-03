/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** game.cpp
*/

#include "game.hpp"

#include "client/src/components/server_entity_id.hpp"
#include "client/src/constants/chat.hpp"
#include "client/src/constants/settings.hpp"
#include "client/src/systems/game/background.hpp"
#include "client/src/systems/game/chat/input.hpp"
#include "client/src/systems/game/chat/messages.hpp"
#include "client/src/systems/game/chat/trigger.hpp"
#include "client/src/systems/game/player.hpp"
#include "client/src/systems/game/sync.hpp"
#include "client/src/systems/ui/input_cursor.hpp"
#include "client/src/ui/input.hpp"
#include "constants/chat.hpp"
#include "constants/settings.hpp"
#include "constants/user.hpp"
#include "libs/mew/src/sets/drawable/drawable.hpp"
#include "libs/mew/src/sets/events/events.hpp"
#include "libs/zygarde/src/core/components/components.hpp"
#include "libs/zygarde/src/physics/2d/systems/systems.hpp"
#include "menu.hpp"
#include "physics/2d/systems/systems.hpp"
#include "src/systems/animations/blink.hpp"
#include "src/systems/animations/fade.hpp"
#include "systems/game/chat/input.hpp"
#include "systems/game/chat/messages.hpp"
#include "systems/game/chat/trigger.hpp"

using namespace mew::sets::events;
using namespace mew::sets::drawable;
using namespace porygon;
using namespace rtype::client::scenes;
using namespace rtype::client::services;
using namespace rtype::client::components;
using namespace rtype::client::systems;
using namespace zygarde::core::types;
using namespace zygarde::core::components;
using namespace mew::sets;

SceneGame::SceneGame(DependenciesHandler::Ptr services) : SceneBase(std::move(services)) {
  auto settings_manager = services_->GetOrThrow<SettingsManager>();
  auto window_manager = services_->GetOrThrow<WindowManager>();
  auto server_connection_service = services_->GetOrThrow<ServerConnectionService>();

  serverConnectionService_ = server_connection_service;

  registry_->RegisterComponent<Tags>();
  registry_->RegisterComponent<ServerEntityId>();
  registry_->RegisterComponent<physics::components::Rigidbody2D>();
  registry_->RegisterComponent<drawable::Rectangle>();

  registry_->AddSystem<GameSyncSystem>(serverConnectionService_, settings_manager);
  registry_->AddSystem<BackgroundSystem>();
  registry_->AddSystem<PlayerSystem>(settings_manager, window_manager, server_connection_service);

  registry_->AddSystem<physics::systems::MovementSystem>(deltaTime_);
  registry_->AddSystem<physics::systems::PositionSystem>();

  const auto username = settings_manager->Get<std::string>(PLAYER_USERNAME);
  registry_->AddSystem<systems::ui::CursorSystem>();
  ui::Input::Create(registry_, "chat",
                    Vector3f{CHAT_PIXELS_LEFT, managers_.window->GetHeight() - 50},
                    {HorizontalAlign::kLeft, VerticalAlign::kCenter}, CHAT_CHAR_SIZE, true);
  registry_->AddSystem<ChatInputSystem>(window_manager, server_connection_service);
  registry_->AddSystem<ChatMessagesSystem>(window_manager, server_connection_service, username,
                                           registry_);
  registry_->AddSystem<ChatTriggerSystem>(window_manager, settings_manager);
  registry_->AddSystem<BlinkSystem>();
  registry_->AddSystem<FadeSystem>();
}

void SceneGame::OnCreate() {
  LoadResources();
  InitFade();
}

void SceneGame::Update(DeltaTime delta_time) {
  deltaTime_ = delta_time;
  registry_->RunSystems();
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

void SceneGame::InitFade() {
  auto rectangle = registry_->SpawnEntity();
  auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  auto point = Vector3f(managers_.window->GetWidth() / 2, managers_.window->GetHeight() / 2);

  registry_->AddComponent<Position>(rectangle, {point, aligns});

  auto color = sf::Color::Black;
  color.a = 0;
  registry_->AddComponent<Drawable>(
      rectangle,
      {Rectangle{color,
                 sf::Color::Transparent,
                 0,
                 {managers_.window->GetWidth() * 100, managers_.window->GetHeight() * 100}},
       WindowManager::View::HUD});
  registry_->AddComponent<Tags>(rectangle, Tags({"end_fade"}));
}
