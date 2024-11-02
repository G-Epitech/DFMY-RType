/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** leaderboard.cpp
*/

#include "leaderboard.hpp"

#include "client/src/systems/leaderboard/sync.hpp"
#include "libs/mew/src/sets/events/events.hpp"
#include "menu.hpp"

using namespace rtype::client;
using namespace rtype::client::scenes;
using namespace mew::sets::events;
using namespace mew::sets::drawable;
using namespace mew::managers;
using namespace zygarde::core::components;
using namespace zygarde::core::types;
using namespace rtype::client::systems;
using namespace rtype::client::services;

SceneLeaderboard::SceneLeaderboard(DependenciesHandler::Ptr services)
        : SceneBase(std::move(services)) {
  this->serverConnectionService_ = services_->GetOrThrow<ServerConnectionService>();

  managers_.sound->LoadSoundBuffer("assets/sounds/button_click.ogg", "buttons:click");

  registry_->AddSystem<LeaderboardSyncSystem>(serverConnectionService_);
}

void SceneLeaderboard::OnCreate() {
  CreateTitle();
  CreateBackButton();
  CreateLeaderboard();
  CreateMainEntity();
}

void SceneLeaderboard::OnActivate() {}

void SceneLeaderboard::Update(std::chrono::nanoseconds delta_time) {
  registry_->RunSystems();
}

void SceneLeaderboard::CreateMainEntity() const {
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

void SceneLeaderboard::CreateTitle() const {
  const auto title = registry_->SpawnEntity();
  const auto point = Vector3f(managers_.window->width_ / 2, 150);
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(title, {point, aligns});
  registry_->AddComponent<Drawable>(title,
                                    {Text{"Leaderboard", "main", 50}, WindowManager::View::HUD});
}

void SceneLeaderboard::CreateBackButton() const {
  const auto exit_button = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  const auto point = Vector3f(managers_.window->width_ / 2, managers_.window->height_ - 50);

  registry_->AddComponent<Position>(exit_button, {point, aligns});
  registry_->AddComponent<Drawable>(exit_button,
                                    {Text{"Back", "main", 20}, WindowManager::View::HUD});
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

void SceneLeaderboard::CreateLeaderboard() const {
  for (std::size_t i = 0; i < 5; i++) {
    CreateLeaderboardEntry("Player " + std::to_string(i), std::to_string((5 - i) * 100), true, i);
  }
}

void SceneLeaderboard::CreateLeaderboardEntry(const std::string &name, const std::string &score, const bool &win,
                                              const std::size_t &index) const {
  const auto rectangleSize = sf::Vector2f(600, 115);
  const auto origin = Vector3f(managers_.window->width_ / 2,
                              ((managers_.window->height_ / 2) - (rectangleSize.y * 2)) +
                              ((rectangleSize.y + 20) * index));
  const auto textOrigin = Vector3f(origin.x - rectangleSize.x / 2, origin.y - rectangleSize.y / 2);

  CreateScoreRectangle(index, rectangleSize, origin);
  CreateScoreTitle(name, textOrigin);
  CreateScoreInfo(score, textOrigin);
  CreateScoreWin(win, textOrigin);
}

void SceneLeaderboard::CreateScoreRectangle(const std::size_t &index, const sf::Vector2f &size, const Vector3f &origin) const {
  const auto entry = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  const auto point = origin;

  registry_->AddComponent<Position>(entry, {point, aligns});
  registry_->AddComponent<Drawable>(
          entry, {Rectangle{sf::Color::Transparent, size, sf::Color::White, 3.0}, WindowManager::View::HUD});
}

void SceneLeaderboard::CreateScoreTitle(const std::string &name, const Vector3f &origin) const {
  const auto title = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kLeft, VerticalAlign::kBottom};
  const auto point = Vector3f(origin.x + 10, origin.y + 25);

  registry_->AddComponent<Position>(title, {point, aligns});
  registry_->AddComponent<Drawable>(title, {Text{"Room: " + name, "main", 20}, WindowManager::View::HUD});
}

void SceneLeaderboard::CreateScoreInfo(const std::string &score, const Vector3f &origin) const {
  const auto info = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kLeft, VerticalAlign::kBottom};
  const auto point = Vector3f(origin.x + 10, origin.y + 60);

  registry_->AddComponent<Position>(info, {point, aligns});
  registry_->AddComponent<Drawable>(info, {Text{"Score: " + score, "main", 20}, WindowManager::View::HUD});
}

void SceneLeaderboard::CreateScoreWin(const bool &win, const Vector3f &origin) const {
  const auto win_entity = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kLeft, VerticalAlign::kBottom};
  const auto point = Vector3f(origin.x + 10, origin.y + 95);

  registry_->AddComponent<Position>(win_entity, {point, aligns});
  registry_->AddComponent<Drawable>(
          win_entity, {Text{win ? "State: Win" : "State: Lose", "main", 20}, WindowManager::View::HUD});
}
