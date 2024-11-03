/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** start.cpp
*/

#include "start.hpp"

#include <utility>

#include "./entities/text_entity.hpp"
#include "client/src/scenes/menu.hpp"
#include "client/src/ui/button/button.hpp"
#include "client/src/ui/select/select.hpp"
#include "create_room.hpp"
#include "libs/mew/src/managers/window_manager.hpp"
#include "libs/zygarde/src/core/components/position/position.hpp"
#include "scenes/lobby.hpp"

using namespace rtype::client::scenes;
using namespace rtype::client::ui;
using namespace zygarde;
using namespace zygarde::core::components;
using namespace zygarde::core::types;
using namespace rtype::client::services;
using namespace porygon;
using namespace mew::managers;

SceneStart::SceneStart(DependenciesHandler::Ptr services) : SceneBase(std::move(services)) {
  roomsService_ = services_->GetOrThrow<RoomsService>();
  Select::RegisterDependencies(registry_);
  TextEntity::RegisterDependencies(registry_);
}

void SceneStart::OnCreate() {
  roomsService_->Refresh();
  CreateStaticLabels();
  CreateControls();
  CreateBackButton();
  CreateNodeSelectLabel();
  CreateRoomSelectLabel();
  CreateSelects();
  CreateRoomInfoArea();
  CreateMainEntity();
}

void SceneStart::Update(DeltaTime delta_time) {
  roomsService_->PollUpdate();
  registry_->RunSystems();
  UpdateSelects();
  {
    auto room_id = Select::GetValue(registry_, "rooms");
    UpdateControls(room_id);
    UpdateRoomInfos(room_id);
  }
}

void SceneStart::CreateStaticLabels() {
  auto center = managers_.window->GetCenter();

  registry_->SpawnEntity<TextEntity>(TextEntity::Properties{
      "Let's start",
      Vector3f(center.x, 150),
      "main",
      50,
      sf::Color::White,
      {HorizontalAlign::kCenter, VerticalAlign::kCenter},
  });
  registry_->SpawnEntity<TextEntity>(TextEntity::Properties{
      "Select a node and a room to start",
      Vector3f(center.x, 210),
      "main",
      17,
      sf::Color::White,
      {HorizontalAlign::kCenter, VerticalAlign::kCenter},
  });
}

Select::Properties SceneStart::GetNodeSelectProps(const RoomsService::RoomsMap &rooms) {
  auto center = managers_.window->GetCenter();
  auto options = std::map<std::string, std::string>();

  for (const auto &[node, _] : rooms) {
    std::string string_id = std::to_string(node);
    options[string_id] = "Node " + string_id;
  }

  return {
      .id = "node",
      .position = Vector3f(center.x - 440, center.y - 180),
      .size = Vector2f(370, 25),
      .placeholder = "No node available",
      .options = options,
      .selectedOption = Select::GetValue(registry_, "node"),
  };
}

void SceneStart::CreateNodeSelectLabel() {
  auto center = managers_.window->GetCenter();
  registry_->SpawnEntity<TextEntity>(TextEntity::Properties{
      "Node",
      Vector3f(center.x - 440, center.y - 210),
      "main",
      13,
      sf::Color::White,
      {HorizontalAlign::kLeft, VerticalAlign::kCenter},
  });
}

Select::Properties SceneStart::GetRoomsSelectProps(
    const RoomsService::RoomsMap &rooms, std::optional<RoomsService::NodeIdType> node_id) {
  auto center = managers_.window->GetCenter();
  auto options = std::map<std::string, std::string>();

  if (node_id && rooms.contains(*node_id)) {
    auto &node = rooms.at(*node_id);
    for (const auto &[room_id, room] : node) {
      std::string string_id = std::to_string(room_id);
      options[string_id] = room.name;
    }
  }

  return {
      .id = "rooms",
      .position = Vector3f(center.x + 70, center.y - 180),
      .size = Vector2f(370, 25),
      .placeholder = "No room available",
      .options = options,
  };
}

void SceneStart::CreateRoomSelectLabel() {
  auto center = managers_.window->GetCenter();
  registry_->SpawnEntity<TextEntity>(TextEntity::Properties{
      "Room",
      Vector3f(center.x + 70, center.y - 210),
      "main",
      13,
      sf::Color::White,
      {HorizontalAlign::kLeft, VerticalAlign::kCenter},
  });
}

void SceneStart::CreateControls() {
  auto center = managers_.window->GetCenter();
  Button::Create(registry_, Button::Properties{
                                .id = "new-room",
                                .label = "New room",
                                .fontName = "main",
                                .position = Vector3f(center.x - 90, center.y - 280),
                                .size = Vector2f(115, 25),
                                .disabled = false,
                                .action =
                                    [this](const sf::Mouse::Button &button, const sf::Vector2f pos,
                                           const MouseEventTarget &target) {
                                      managers_.scenes->GoToScene<SceneCreateRoom>();
                                    },
                            });
  Button::Create(registry_,
                 Button::Properties{
                     .id = "refresh",
                     .label = "Refresh",
                     .fontName = "main",
                     .position = Vector3f(center.x - 210, center.y - 280),
                     .size = Vector2f(100, 25),
                     .disabled = false,
                     .action = [this](const sf::Mouse::Button &button, const sf::Vector2f pos,
                                      const MouseEventTarget &target) { roomsService_->Refresh(); },
                 });
  Button::Create(registry_,
                 Button::Properties{
                     .id = "play",
                     .label = "Join room",
                     .fontName = "main",
                     .position = Vector3f(center.x + 60, center.y - 280),
                     .size = Vector2f(150, 25),
                     .disabled = false,
                     .color = sf::Color(17, 21, 138),
                     .action = [this](const sf::Mouse::Button &button, const sf::Vector2f pos,
                                      const MouseEventTarget &target) { OnJoinRoom(); },
                 });
}

void SceneStart::CreateMainEntity() {
  const auto main = registry_->SpawnEntity();

  registry_->AddComponent<OnMousePressed>(
      main,
      OnMousePressed{.strategy = MouseEventTarget::kAnyTarget,
                     .handler = [this](const sf::Mouse::Button &button, const sf::Vector2f &pos,
                                       const MouseEventTarget &target) {
                       if (button == sf::Mouse::Button::Left) {
                         managers_.sound->PlaySound("buttons:click");
                       }
                     }});
}

void SceneStart::CreateBackButton() {
  const auto exit_button = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  const auto point = Vector3f(managers_.window->GetWidth() / 2, managers_.window->GetHeight() - 50);

  registry_->AddComponent<Position>(exit_button, {point, aligns});
  registry_->AddComponent<Drawable>(exit_button, {Text{"Back", "main", 20}, WindowManager::HUD});
  registry_->AddComponent<OnMousePressed>(
      exit_button,
      OnMousePressed{.strategy = MouseEventTarget::kLocalTarget,
                     .handler = [this](const sf::Mouse::Button &button, const sf::Vector2f &pos,
                                       const MouseEventTarget &target) {
                       if (button == sf::Mouse::Button::Left) {
                         managers_.scenes->GoToScene<SceneMenu>();
                       }
                     }});
  registry_->AddComponent<OnMouseMoved>(
      exit_button, OnMouseMoved{.strategy = MouseEventTarget::kAnyTarget,
                                .handler = [this, exit_button](const sf::Vector2f &pos,
                                                               const MouseEventTarget &target) {
                                  auto drawables = registry_->GetComponents<Drawable>();

                                  auto &dr = (*drawables)[static_cast<std::size_t>(exit_button)];

                                  if (dr) {
                                    auto &drawable = dr.value();
                                    auto &variant = drawable.drawable;

                                    if (std::holds_alternative<Text>(variant)) {
                                      auto &text = std::get<Text>(variant);
                                      if (target == MouseEventTarget::kLocalTarget) {
                                        text.style = sf::Text::Style::Underlined;
                                      } else {
                                        text.style = sf::Text::Style::Regular;
                                      }
                                    }
                                  }
                                }});
}

void SceneStart::UpdateSelects() {
  if (roomsService_->GetLastRefreshTime() <= lastRefreshTime_) {
    return;
  }
  lastRefreshTime_ = roomsService_->GetLastRefreshTime();
  auto rooms = roomsService_->GetRooms();
  Select::Update(registry_, GetNodeSelectProps(rooms));
  UpdateSelectedNode();
  Select::Update(registry_, GetRoomsSelectProps(rooms, selectedNode_));
}

void SceneStart::CreateSelects() {
  auto rooms = roomsService_->GetRooms();

  Select::Create(registry_, GetNodeSelectProps(rooms));
  UpdateSelectedNode();
  Select::Create(registry_, GetRoomsSelectProps(rooms, selectedNode_));
}

void SceneStart::UpdateSelectedNode() {
  auto str_id = Select::GetValue(registry_, "node");
  if (str_id) {
    try {
      selectedNode_ = std::stoul(*str_id);
    } catch (const std::exception &e) {
      std::cerr << "Invalid node id: " << *str_id << std::endl;
    }
  }
}

void SceneStart::UpdateControls(const std::optional<std::string> &room_id) {
  auto selected_room = Select::GetValue(registry_, "rooms");

  Button::SetEnabled(registry_, "play", selected_room.has_value());
  Button::SetEnabled(registry_, "new-room", roomsService_->CanCreateRoom());
}

void SceneStart::CreateRoomInfoArea() {
  const auto center = managers_.window->GetCenter();
  const auto entity = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kLeft, VerticalAlign::kTop};
  const auto rectangle = mew::sets::drawable::Rectangle{
      .fillColor = sf::Color::Transparent,
      .outlineColor = sf::Color::White,
      .outlineThickness = 2.0,
      .size = {880, 200},
  };
  registry_->AddComponent<Position>(entity, {Vector3f(center.x - 440, center.y - 100), aligns});
  registry_->AddComponent<Drawable>(entity, {rectangle, WindowManager::View::HUD});
  registry_->SpawnEntity<TextEntity>(TextEntity::Properties{
      "Room infos",
      Vector3f(center.x - 440, center.y - 110),
      "main",
      13,
      sf::Color::White,
      {HorizontalAlign::kLeft, VerticalAlign::kBottom},
  });
  CreateRoomInfosContent();
}

void SceneStart::CreateRoomInfosContent() {
  static const std::unordered_map<std::string, std::string> infos = {
      {"nb-players-max", "Max number of players"},
      {"nb-players", "Number of players"},
      {"difficulty", "Difficulty"},
      {"name", "Name"},
  };
  const auto center = managers_.window->GetCenter();
  const auto aligns = Alignment{HorizontalAlign::kLeft, VerticalAlign::kBottom};
  auto y = center.y - 70;
  const auto step = 30;

  for (const auto &[key, label] : infos) {
    y += step;
    registry_->SpawnEntity<TextEntity>(
        TextEntity::Properties{.text = label + ":",
                               .position = Vector3f(center.x - 410, y),
                               .fontName = "main",
                               .characterSize = 13,
                               .color = sf::Color::White,
                               .alignment = aligns,
                               .tags = {"room-info-label"},
                               .visible = true});
    registry_->SpawnEntity<TextEntity>(TextEntity::Properties{
        .text = label + ":",
        .position = Vector3f(center.x - 90, y),
        .fontName = "main",
        .characterSize = 13,
        .color = sf::Color::White,
        .alignment = aligns,
        .tags = {"room-info-" + key},
        .visible = true,
    });
  }

  registry_->SpawnEntity<TextEntity>(TextEntity::Properties{
      .text = "No room selected",
      .position = Vector3f(center.x, center.y),
      .fontName = "main",
      .characterSize = 13,
      .color = sf::Color::White,
      .alignment = {HorizontalAlign::kCenter, VerticalAlign::kCenter},
      .style = sf::Text::Style::Italic,
      .tags = {"room-info-no-room"},
      .visible = false,
  });
}

void SceneStart::UpdateRoomInfos(const std::optional<std::string> &room_id) {
  auto rooms = roomsService_->GetRooms();
  auto tags = registry_->GetMatchingEntities<Drawable, Tags>();

  if (!room_id || !selectedNode_ || !rooms.contains(*selectedNode_)) {
    HideRoomInfo();
    return;
  }
  try {
    auto room_sub_id = std::stoul(*room_id);
    auto &node = rooms.at(*selectedNode_);

    if (!node.contains(room_sub_id)) {
      return HideRoomInfo();
    }
    SetRoomInfo(node.at(room_sub_id));
  } catch (const std::exception &e) {
    HideRoomInfo();
    return;
  }
}

void SceneStart::SetRoomInfo(const RoomsService::RoomStatusType &room) {
  auto components = registry_->GetMatchingEntities<Drawable, Tags>();

  for (auto &&[drawable, tags] : components) {
    if (tags & "room-info-no-room") {
      drawable.visible = false;
      continue;
    } else if (!std::holds_alternative<Text>(drawable.drawable)) {
      continue;
    }
    auto &text = std::get<Text>(drawable.drawable);
    if (tags & "room-info-label") {
      drawable.visible = true;
    } else if (tags & "room-info-name") {
      text.text = room.name;
      drawable.visible = true;
    } else if (tags & "room-info-difficulty") {
      text.text = std::to_string(room.difficulty);
      drawable.visible = true;
    } else if (tags & "room-info-nb-players") {
      text.text = std::to_string(room.nbPlayers);
      drawable.visible = true;
    } else if (tags & "room-info-nb-players-max") {
      text.text = std::to_string(room.nbPlayersMax);
      drawable.visible = true;
    }
  }
}

void SceneStart::HideRoomInfo() {
  auto components = registry_->GetMatchingEntities<Drawable, Tags>();
  static const std::vector<std::string> props = {
      "label", "name", "difficulty", "nb-players", "nb-players-max",
  };
  for (auto &&[drawable, tags] : components) {
    if (tags & "room-info-no-room") {
      drawable.visible = true;
      continue;
    }
    for (const auto &prop : props) {
      if (tags & ("room-info-" + prop)) {
        drawable.visible = false;
      }
    }
  }
}
void SceneStart::OnJoinRoom() {
  auto room_id_str = Select::GetValue(registry_, "rooms");
  if (!room_id_str || !selectedNode_) {
    return;
  }
  try {
    auto room_id = std::stoull(*room_id_str);
    auto res = roomsService_->JoinRoom(*selectedNode_, room_id);
    if (res) {
      managers_.scenes->GoToScene<SceneLobby>();
    } else {
      std::cerr << "Unable to join the room" << std::endl;
    }
  } catch (const std::exception &e) {
    std::cerr << "Invalid room id: " << *room_id_str << std::endl;
  }
}
