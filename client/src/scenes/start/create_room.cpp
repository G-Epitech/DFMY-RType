/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** create_room.cpp
*/

#include "create_room.hpp"

#include "client/src/systems/register/connection.hpp"
#include "client/src/systems/ui/input_cursor.hpp"
#include "client/src/ui/input.hpp"
#include "libs/mew/src/sets/events/events.hpp"
#include "scenes/lobby.hpp"
#include "start.hpp"
#include "systems/animations/blink.hpp"

using namespace rtype::client::scenes;
using namespace rtype::client::services;
using namespace rtype::client::systems;
using namespace mew::sets::drawable;
using namespace mew::sets::events;
using namespace mew::managers;
using namespace zygarde::core::components;
using namespace zygarde::core::types;

SceneCreateRoom::SceneCreateRoom(DependenciesHandler::Ptr services)
    : SceneBase(std::move(services)) {
  registry_->RegisterComponent<Tags>();
  registry_->AddSystem<BlinkSystem>();
  constexpr Alignment alignment{HorizontalAlign::kLeft, VerticalAlign::kCenter};
  registry_->AddSystem<systems::ui::CursorSystem>(alignment);
  const Vector3f pos{CREATE_ROOM_PIXEL_LEFT + 40, managers_.window->GetHeight() / 2 - 50, 0};

  ui::Input::Create(registry_, "create_room", pos, alignment, 20);
  serverConnectionService_ = services_->GetOrThrow<ServerConnectionService>();
  settingsManager_ = services_->GetOrThrow<SettingsManager>();
  scenesManager_ = services_->GetOrThrow<ScenesManager>();
}

void SceneCreateRoom::OnCreate() {
  CreateTitle();
  CreateInputLabel();
  CreateDifficulty();
  CreateNbPlayers();
  CreateCreateButton();
  CreateBackButton();
}

void SceneCreateRoom::OnActivate() {
  difficulty_ = 0;
  nbPlayers_ = 1;
  const auto all_tags = registry_->GetComponents<Tags>();
  const auto all_drawables = registry_->GetComponents<Drawable>();
  if (!all_tags || !all_drawables)
    return;
  for (std::size_t i = 0; i < all_tags->size(); i++) {
    if (!(*all_tags)[i])
      continue;
    if ((*all_tags)[i].value() & "create_room_input") {
      (*all_tags)[i]->RemoveTag("disabled");
      if (i < all_drawables->size() && (*all_drawables)[i]) {
        (*all_drawables)[i]->drawable = Text{"", "main", 20};
      }
    }
  }
}

void SceneCreateRoom::CreateTitle() const {
  const auto title = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  const auto point =
      Vector3f(managers_.window->GetWidth() / 2, managers_.window->GetHeight() / 2 - 250);

  registry_->AddComponent<Position>(title, {point, aligns});
  registry_->AddComponent<Drawable>(title,
                                    {Text{"Create a Room", "main", 60}, WindowManager::View::HUD});
}

void SceneCreateRoom::CreateCreateButton() const {
  const auto connect_button = registry_->SpawnEntity();
  const auto point =
      Vector3f(managers_.window->GetWidth() / 2, managers_.window->GetHeight() / 2 + 150);
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(connect_button, {point, aligns});
  registry_->AddComponent<Drawable>(connect_button,
                                    {Text{"Create", "main", 20}, WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      connect_button,
      OnMousePressed{.strategy = MouseEventTarget::kLocalTarget,
                     .handler = [this](const sf::Mouse::Button& button, const sf::Vector2f& pos,
                                       const MouseEventTarget& target) {
                       if (button == sf::Mouse::Button::Left) {
                         const auto all_tags = registry_->GetComponents<Tags>();
                         const auto all_drawables = registry_->GetComponents<Drawable>();
                         if (!all_tags || !all_drawables)
                           return;
                         for (std::size_t i = 0; i < all_tags->size(); i++) {
                           if (!(*all_tags)[i])
                             continue;
                           if ((*all_tags)[i].value() & "create_room_input") {
                             auto& drawable = (*all_drawables)[i];
                             auto& text = std::get<Text>(drawable->drawable);
                             if (text.text.empty() || difficulty_ == 0 || nbPlayers_ == 0) {
                               return;
                             }
                             api::payload::CreateRoom payload{};
                             payload.difficulty = difficulty_ - 2;
                             payload.nbPlayers = nbPlayers_ - 1;
                             char usernameChar[20] = {0};
                             strncpy(usernameChar, text.text.c_str(), sizeof(usernameChar) - 1);
                             std::memcpy(payload.name, usernameChar, sizeof(payload.name));
                             auto res = serverConnectionService_->client()->CreateRoom(payload);
                             if (res) {
                               scenesManager_->GoToScene<SceneStart>();
                               (*all_tags)[i]->AddTag("disabled");
                             }
                           }
                         }
                       }
                     }});
  registry_->AddComponent<OnMouseMoved>(
      connect_button,
      OnMouseMoved{.strategy = MouseEventTarget::kAnyTarget,
                   .handler = [this, connect_button](const sf::Vector2f& pos,
                                                     const MouseEventTarget& target) {
                     auto drawables = registry_->GetComponents<Drawable>();

                     auto& dr = (*drawables)[static_cast<std::size_t>(connect_button)];

                     if (dr) {
                       auto& drawable = dr.value();
                       auto& variant = drawable.drawable;

                       if (std::holds_alternative<Text>(variant)) {
                         auto& text = std::get<Text>(variant);
                         if (difficulty_ == 0 || nbPlayers_ == 0) {
                           text.style = sf::Text::Style::Regular;
                           text.color = sf::Color::White;
                           return;
                         }
                         if (target == MouseEventTarget::kLocalTarget) {
                           text.style = sf::Text::Style::Underlined;
                           text.color = sf::Color::Green;
                         } else {
                           text.style = sf::Text::Style::Regular;
                           text.color = sf::Color::White;
                         }
                       }
                     }
                   }});
}

void SceneCreateRoom::CreateBackButton() const {
  const auto exit_button = registry_->SpawnEntity();
  const auto point = Vector3f(managers_.window->GetWidth() / 2, managers_.window->GetHeight() - 50);
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  registry_->AddComponent<Position>(exit_button, {point, aligns});
  registry_->AddComponent<Drawable>(exit_button,
                                    {Text{"Back", "main", 20}, WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      exit_button,
      OnMousePressed{.strategy = MouseEventTarget::kLocalTarget,
                     .handler = [this](const sf::Mouse::Button& button, const sf::Vector2f& pos,
                                       MouseEventTarget target) {
                       if (button == sf::Mouse::Button::Left) {
                         managers_.scenes->GoToScene<SceneStart>();
                       }
                     }});
  registry_->AddComponent<OnMouseMoved>(
      exit_button, OnMouseMoved{.strategy = MouseEventTarget::kAnyTarget,
                                .handler = [this, exit_button](const sf::Vector2f& pos,
                                                               const MouseEventTarget& target) {
                                  auto drawables = registry_->GetComponents<Drawable>();

                                  auto& dr = (*drawables)[static_cast<std::size_t>(exit_button)];

                                  if (dr) {
                                    auto& drawable = dr.value();
                                    auto& variant = drawable.drawable;

                                    if (std::holds_alternative<Text>(variant)) {
                                      auto& text = std::get<Text>(variant);
                                      if (target == MouseEventTarget::kLocalTarget) {
                                        text.style = sf::Text::Style::Underlined;
                                      } else {
                                        text.style = sf::Text::Style::Regular;
                                      }
                                    }
                                  }
                                }});
}

void SceneCreateRoom::CreateInputLabel() {
  const auto input_label = registry_->SpawnEntity();
  const auto point = Vector3f(CREATE_ROOM_PIXEL_LEFT, managers_.window->GetHeight() / 2 - 50);
  constexpr auto aligns = Alignment{HorizontalAlign::kRight, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(input_label, {point, aligns});
  registry_->AddComponent<Drawable>(input_label,
                                    {Text{"Name :", "main", 20}, WindowManager::View::HUD});
}

void SceneCreateRoom::CreateDifficulty() {
  CreateDifficultyLabel();
  CreateDifficultyNumbers();
}

void SceneCreateRoom::CreateDifficultyLabel() {
  const auto difficulty_text = registry_->SpawnEntity();
  const auto point = Vector3f(CREATE_ROOM_PIXEL_LEFT, managers_.window->GetHeight() / 2);
  const auto aligns = Alignment{HorizontalAlign::kRight, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(difficulty_text, {point, aligns});
  registry_->AddComponent<Drawable>(difficulty_text,
                                    {Text{"Difficulty :", "main", 20}, WindowManager::View::HUD});
}

void SceneCreateRoom::CreateDifficultyNumbers() {
  for (unsigned int i = 1; i <= 5; i++) {
    CreateDifficultyNumber(i, {CREATE_ROOM_PIXEL_LEFT + 40 + static_cast<float>(i - 1) * 40,
                               managers_.window->GetHeight() / 2});
  }
}

void SceneCreateRoom::CreateDifficultyNumber(unsigned int number, const sf::Vector2f& pos) {
  const auto difficulty_number = registry_->SpawnEntity();
  constexpr auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(difficulty_number, {Vector3f{pos.x, pos.y, 0}, aligns});
  registry_->AddComponent<Drawable>(
      difficulty_number, {Text{std::to_string(number), "main", 20}, WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      difficulty_number,
      OnMousePressed{.strategy = MouseEventTarget::kLocalTarget,
                     .handler = [this, difficulty_number, number](const sf::Mouse::Button& button,
                                                                  const sf::Vector2f& pos,
                                                                  const MouseEventTarget& target) {
                       if (button == sf::Mouse::Button::Left) {
                         difficulty_ = number + 1;
                         auto drawables = registry_->GetComponents<Drawable>();

                         auto& dr = (*drawables)[static_cast<std::size_t>(difficulty_number)];

                         if (dr) {
                           auto& drawable = dr.value();
                           auto& variant = drawable.drawable;

                           if (std::holds_alternative<Text>(variant)) {
                             auto& text = std::get<Text>(variant);
                             if (target == MouseEventTarget::kLocalTarget) {
                               text.style = sf::Text::Style::Underlined;
                             } else {
                               text.style = sf::Text::Style::Regular;
                             }
                           }
                         }
                       }
                     }});

  registry_->AddComponent<OnMouseMoved>(
      difficulty_number,
      OnMouseMoved{.strategy = MouseEventTarget::kAnyTarget,
                   .handler = [this, difficulty_number, number](const sf::Vector2f& pos,
                                                                const MouseEventTarget& target) {
                     auto drawables = registry_->GetComponents<Drawable>();

                     auto& dr = (*drawables)[static_cast<std::size_t>(difficulty_number)];

                     if (dr) {
                       auto& drawable = dr.value();
                       auto& variant = drawable.drawable;

                       if (std::holds_alternative<Text>(variant)) {
                         auto& text = std::get<Text>(variant);
                         if (target == MouseEventTarget::kLocalTarget) {
                           text.style = sf::Text::Style::Underlined;
                         } else {
                           if (difficulty_ != number + 1) {
                             text.style = sf::Text::Style::Regular;
                           }
                         }
                       }
                     }
                   }});
}

void SceneCreateRoom::CreateNbPlayers() {
  CreateNbPlayersLabel();
  CreateNbPlayersNumbers();
}

void SceneCreateRoom::CreateNbPlayersLabel() {
  const auto nb_players_text = registry_->SpawnEntity();
  const auto point = Vector3f(CREATE_ROOM_PIXEL_LEFT, managers_.window->GetHeight() / 2 + 50);
  const auto aligns = Alignment{HorizontalAlign::kRight, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(nb_players_text, {point, aligns});
  registry_->AddComponent<Drawable>(nb_players_text,
                                    {Text{"Nb Players :", "main", 20}, WindowManager::View::HUD});
}

void SceneCreateRoom::CreateNbPlayersNumbers() {
  for (unsigned int i = 1; i <= 4; i++) {
    CreateNbPlayersNumber(i, {CREATE_ROOM_PIXEL_LEFT + 40 + static_cast<float>(i - 1) * 40,
                              managers_.window->GetHeight() / 2 + 50});
  }
}

void SceneCreateRoom::CreateNbPlayersNumber(unsigned int number, const sf::Vector2f& pos) {
  const auto nb_players_number = registry_->SpawnEntity();
  constexpr auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(nb_players_number, {Vector3f{pos.x, pos.y, 0}, aligns});
  registry_->AddComponent<Drawable>(
      nb_players_number, {Text{std::to_string(number), "main", 20}, WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      nb_players_number,
      OnMousePressed{.strategy = MouseEventTarget::kLocalTarget,
                     .handler = [this, nb_players_number, number](const sf::Mouse::Button& button,
                                                                  const sf::Vector2f&,
                                                                  const MouseEventTarget& target) {
                       if (button == sf::Mouse::Button::Left) {
                         nbPlayers_ = number + 1;
                         auto drawables = registry_->GetComponents<Drawable>();

                         auto& dr = (*drawables)[static_cast<std::size_t>(nb_players_number)];

                         if (dr) {
                           auto& drawable = dr.value();
                           auto& variant = drawable.drawable;

                           if (std::holds_alternative<Text>(variant)) {
                             auto& text = std::get<Text>(variant);
                             if (target == MouseEventTarget::kLocalTarget) {
                               text.style = sf::Text::Style::Underlined;
                             } else {
                               text.style = sf::Text::Style::Regular;
                             }
                           }
                         }
                       }
                     }});

  registry_->AddComponent<OnMouseMoved>(
      nb_players_number,
      OnMouseMoved{.strategy = MouseEventTarget::kAnyTarget,
                   .handler = [this, nb_players_number, number](const sf::Vector2f& pos,
                                                                const MouseEventTarget& target) {
                     auto drawables = registry_->GetComponents<Drawable>();

                     auto& dr = (*drawables)[static_cast<std::size_t>(nb_players_number)];

                     if (dr) {
                       auto& drawable = dr.value();
                       auto& variant = drawable.drawable;

                       if (std::holds_alternative<Text>(variant)) {
                         auto& text = std::get<Text>(variant);
                         if (target == MouseEventTarget::kLocalTarget) {
                           text.style = sf::Text::Style::Underlined;
                         } else {
                           if (nbPlayers_ != number + 1) {
                             text.style = sf::Text::Style::Regular;
                           }
                         }
                       }
                     }
                   }});
}
