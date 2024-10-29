/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** menu.cpp
*/

#include "lobby.hpp"

#include "./game.hpp"
#include "libs/mew/src/sets/drawable/drawable.hpp"

using namespace rtype::client::scenes;
using namespace rtype::client::services;
using namespace zygarde::core::components;
using namespace zygarde::core::types;
using namespace porygon;
using namespace mew::sets::drawable;
using namespace mew::scenes;
using namespace mew::managers;

SceneLobby::SceneLobby(DependenciesHandler::Ptr services) : SceneBase(std::move(services)) {
  serverConnectionService_ = services_->GetOrThrow<ServerConnectionService>();
  registry_->RegisterComponent<Tags>();
}

SceneLobby::~SceneLobby() {
  if (joiningThread_ && joiningThread_->joinable()) {
    joiningThread_->join();
  }
}

void SceneLobby::OnCreate() {
  CreateGEpitechLogo();
  CreateStatusText();
}

void SceneLobby::OnActivate() {
  if (status_ == LobbyStatus::kIn) {
    return managers_.scenes->GoToScene<SceneGame>();
  }
  JoinLobbyAsync();
}

void SceneLobby::Update(std::chrono::nanoseconds delta_time) {
  UpdateStatusText();
  registry_->RunSystems();
  if (status_ == LobbyStatus::kIn) {
    managers_.scenes->GoToScene<SceneGame>();
  }
}

void SceneLobby::CreateStatusText() {
  const auto main_text = registry_->SpawnEntity();
  const auto secondary_text = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  const auto base = Vector3f(managers_.window->width_ / 2, managers_.window->height_ / 2 + 250);

  registry_->AddComponent<Position>(main_text, {base, aligns});
  registry_->AddComponent<Tags>(main_text, Tags({"main_status_text"}));
  registry_->AddComponent<Drawable>(
      main_text, {Text{"Main Status text", "main", 20}, WindowManager::View::HUD});
  registry_->AddComponent<Position>(secondary_text, {base + Vector3f{0, 50}, aligns});
  registry_->AddComponent<Tags>(secondary_text, Tags({"secondary_status_text"}));
  registry_->AddComponent<Drawable>(
      secondary_text, {Text{"Secondary Status text", "main", 12}, WindowManager::View::HUD});
}

void SceneLobby::CreateGEpitechLogo() {
  const auto logo = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  const auto point = Vector3f(managers_.window->width_ / 2, managers_.window->height_ / 2 - 150);
  const auto rect = sf::IntRect{0, 0, 927, 927};
  registry_->AddComponent<Position>(logo, {point, aligns});
  registry_->AddComponent<Drawable>(

      logo,
      {Texture{.name = "g-epitech-logo", .scale = 0.35, .rect = rect}, WindowManager::View::HUD});
}

void SceneLobby::JoinLobbyAsync() {
  if (joiningThread_)
    return;
  joiningThread_ = std::thread(&SceneLobby::JoinLobby, this);
}

void SceneLobby::JoinLobby() {
  if (status_ == LobbyStatus::kJoining) {
    return;
  }
  mainMessage_ = "Registering to the server";
  secondaryMessage_ = "Please wait...";
  auto res = serverConnectionService_->client()->Register({.pseudo = "Pti't plouf"});
  if (!res) {
    mainMessage_ = "Registration failed";
    secondaryMessage_ = "Unable to register on the server";
    status_ = LobbyStatus::kFailed;
    return;
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(1200));
  status_ = LobbyStatus::kRegistered;
  mainMessage_ = "Joining the lobby";
  secondaryMessage_ = "Please wait...";
  res = serverConnectionService_->client()->JoinLobby({.lobbyId = 0});
  if (!res) {
    mainMessage_ = "Joining failed";
    secondaryMessage_ = "Unable to join the lobby";
    status_ = LobbyStatus::kFailed;
    return;
  }
  mainMessage_ = "Success";
  secondaryMessage_ = "You are now in the lobby. The game will start soon";
  std::this_thread::sleep_for(std::chrono::milliseconds(1200));
  status_ = LobbyStatus::kIn;
}

void SceneLobby::UpdateStatusText() {
  auto drawables = registry_->GetComponents<Drawable>();
  auto tags = registry_->GetComponents<Tags>();
  std::size_t main_text_id = 0;
  std::size_t secondary_text_id = 0;
  std::size_t i = 0;

  for (auto &tag : *tags) {
    if (!tag) {
      i += 1;
      continue;
    } else if ((*tag) & "main_status_text") {
      main_text_id = i;
    } else if ((*tag) & "secondary_status_text") {
      secondary_text_id = i;
    }
    i += 1;
  }
  auto &main_text = (*drawables)[main_text_id];
  auto &secondary_text = (*drawables)[secondary_text_id];
  if (!main_text || !secondary_text) {
    return;
  }
  try {
    auto &main_text_component = std::get<Text>((*main_text).drawable);
    auto &secondary_text_component = std::get<Text>((*secondary_text).drawable);
    main_text_component.text = mainMessage_;
    secondary_text_component.text = secondaryMessage_;
  } catch (const std::bad_variant_access &e) {
    return;
  }
}
