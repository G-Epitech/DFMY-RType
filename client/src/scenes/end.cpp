/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** leaderboard.cpp
*/

#include "end.hpp"

#include "client/src/systems/leaderboard/sync.hpp"
#include "constants/game.hpp"
#include "constants/settings.hpp"
#include "libs/mew/src/sets/events/events.hpp"
#include "menu.hpp"

using namespace rtype::client;
using namespace rtype::client::scenes;
using namespace mew::sets::events;
using namespace mew::sets;
using namespace mew::sets::drawable;
using namespace mew::managers;
using namespace zygarde::core::components;
using namespace zygarde::core::types;
using namespace rtype::client::systems;
using namespace rtype::client::services;

SceneEnd::SceneEnd(DependenciesHandler::Ptr services) : SceneBase(std::move(services)) {
  serverConnectionService_ = services_->GetOrThrow<ServerConnectionService>();
  settingsManager_ = services_->GetOrThrow<SettingsManager>();
}

void SceneEnd::OnCreate() {
  const Vector3f origin{managers_.window->GetWidth() / 2, managers_.window->GetHeight() / 2};
  constexpr Alignment textAligns{HorizontalAlign::kCenter, VerticalAlign::kCenter};

  CreateWin(origin, textAligns);
  CreateScore(origin, textAligns);
  CreateTime(origin, textAligns);
  CreateBackButton();
  CreateMainEntity();
}

void SceneEnd::OnActivate() {}

void SceneEnd::CreateMainEntity() const {
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

void SceneEnd::CreateBackButton() const {
  const auto exit_button = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  const auto point = Vector3f(managers_.window->GetWidth() / 2, managers_.window->GetHeight() - 50);

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

void SceneEnd::CreateWin(const zygarde::core::types::Vector3f &origin,
                         const Alignment &aligns) const {
  const auto win_entity = registry_->SpawnEntity();
  const auto point = Vector3f(origin.x, origin.y - 150);
  const bool win = settingsManager_->Get<bool>(GAME_END_WIN);
  const auto text = win ? "Win" : "Lose";
  const auto color = win ? sf::Color::Green : sf::Color::Red;

  registry_->AddComponent<Position>(win_entity, {point, aligns});
  registry_->AddComponent<Drawable>(
      win_entity, {Text{text, "main", 50, sf::Text::Style::Bold, color}, WindowManager::View::HUD});
}

void SceneEnd::CreateScore(const zygarde::core::types::Vector3f &origin,
                           const Alignment &aligns) const {
  const auto title = registry_->SpawnEntity();
  const auto point = Vector3f(origin.x, origin.y);
  const auto score = settingsManager_->Get<std::size_t>(GAME_END_SCORE);
  const auto text = "Score: " + std::to_string(score);

  registry_->AddComponent<Position>(title, {point, aligns});
  registry_->AddComponent<Drawable>(title, {Text{text, "main", 25}, WindowManager::View::HUD});
}

void SceneEnd::CreateTime(const zygarde::core::types::Vector3f &origin,
                          const Alignment &aligns) const {
  const auto info = registry_->SpawnEntity();
  const auto point = Vector3f(origin.x, origin.y + 30);
  const auto time = settingsManager_->Get<time_t>(GAME_END_TIME);

  const auto *localTime = std::localtime(&time);

  char buffer[6] = {0};
  std::strftime(buffer, sizeof(buffer), "%M:%S", localTime);
  const std::string text_time(buffer);
  const std::string text = "Time: " + text_time;

  registry_->AddComponent<Position>(info, {point, aligns});
  registry_->AddComponent<Drawable>(info, {Text{text, "main", 20}, WindowManager::View::HUD});
}
