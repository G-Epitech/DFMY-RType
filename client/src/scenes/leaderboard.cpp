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
using namespace mew::sets;
using namespace mew::sets::drawable;
using namespace mew::managers;
using namespace zygarde::core::components;
using namespace zygarde::core::types;
using namespace rtype::client::systems;
using namespace rtype::client::services;

SceneLeaderboard::SceneLeaderboard(DependenciesHandler::Ptr services)
    : SceneBase(std::move(services)) {
  this->scores_ = std::make_shared<std::vector<payload::Score>>();
  this->serverConnectionService_ = services_->GetOrThrow<ServerConnectionService>();

  registry_->AddSystem<LeaderboardSyncSystem>(serverConnectionService_, scores_);
  registry_->RegisterComponent<Tags>();
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
  UpdateLeaderboard();
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
  const auto rectangleSize = sf::Vector2f(600, 115);

  for (std::size_t i = 0; i < 5; i++) {
    const auto origin = Vector3f(
        managers_.window->width_ / 2,
        ((managers_.window->height_ / 2) - (rectangleSize.y * 2)) + ((rectangleSize.y + 20) * i));
    const auto textOrigin =
        Vector3f(origin.x - rectangleSize.x / 2, origin.y - rectangleSize.y / 2);

    CreateScoreRectangle(i, rectangleSize, origin);
    CreateScoreTitle(i, textOrigin);
    CreateScoreInfo(i, textOrigin);
    CreateScoreWin(i, textOrigin);
  }
}

void SceneLeaderboard::UpdateLeaderboard() const {
  for (std::size_t i = 0; i < scores_->size(); i++) {
    const auto &score = scores_->at(i);
    UpdateLeaderboardEntry(score.name, std::to_string(score.score), score.win, i);
  }
}

void SceneLeaderboard::UpdateLeaderboardEntry(const std::string &name, const std::string &score,
                                              const bool &win, const std::size_t &index) const {
  UpdateScoreTitle(index, name);
  UpdateScoreInfo(index, score);
  UpdateScoreWin(index, win);
}

void SceneLeaderboard::CreateScoreRectangle(const std::size_t &index, const sf::Vector2f &size,
                                            const Vector3f &origin) const {
  const auto entry = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};
  const auto point = origin;

  registry_->AddComponent<Position>(entry, {point, aligns});
  registry_->AddComponent<Drawable>(
      entry,
      {drawable::Rectangle{sf::Color::Transparent, size, sf::Color::White, 3.0}, WindowManager::View::HUD});
}

void SceneLeaderboard::CreateScoreTitle(const std::size_t &index,
                                        const zygarde::core::types::Vector3f &origin) const {
  const auto title = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kLeft, VerticalAlign::kBottom};
  const auto point = Vector3f(origin.x + 10, origin.y + 25);

  registry_->AddComponent<Tags>(title, Tags({"title_" + std::to_string(index)}));
  registry_->AddComponent<Position>(title, {point, aligns});
  registry_->AddComponent<Drawable>(title, {Text{"", "main", 20}, WindowManager::View::HUD});
}

void SceneLeaderboard::CreateScoreInfo(const std::size_t &index,
                                       const zygarde::core::types::Vector3f &origin) const {
  const auto info = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kLeft, VerticalAlign::kBottom};
  const auto point = Vector3f(origin.x + 10, origin.y + 60);

  registry_->AddComponent<Tags>(info, Tags({"score_" + std::to_string(index)}));
  registry_->AddComponent<Position>(info, {point, aligns});
  registry_->AddComponent<Drawable>(info, {Text{"", "main", 20}, WindowManager::View::HUD});
}

void SceneLeaderboard::CreateScoreWin(const std::size_t &index,
                                      const zygarde::core::types::Vector3f &origin) const {
  const auto win_entity = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kLeft, VerticalAlign::kBottom};
  const auto point = Vector3f(origin.x + 10, origin.y + 95);

  registry_->AddComponent<Tags>(win_entity, Tags({"win_" + std::to_string(index)}));
  registry_->AddComponent<Position>(win_entity, {point, aligns});
  registry_->AddComponent<Drawable>(win_entity, {Text{"", "main", 20}, WindowManager::View::HUD});
}

void SceneLeaderboard::UpdateScoreTitle(const std::size_t &index, const std::string &name) const {
  const auto tags = registry_->GetComponents<Tags>();
  std::size_t entityIndex = 0;

  for (const auto &tag : *tags) {
    if (tag && *tag & ("title_" + std::to_string(index))) {
      break;
    }
    entityIndex++;
  }

  const auto entity = registry_->EntityFromIndex(entityIndex);
  const auto drawComponent = registry_->GetComponent<Drawable>(entity);
  drawComponent.value()->drawable = Text{"Room: " + name, "main", 20};
}

void SceneLeaderboard::UpdateScoreInfo(const std::size_t &index, const std::string &score) const {
  const auto tags = registry_->GetComponents<Tags>();
  std::size_t entityIndex = 0;

  for (const auto &tag : *tags) {
    if (tag && *tag & ("score_" + std::to_string(index))) {
      break;
    }
    entityIndex++;
  }

  const auto entity = registry_->EntityFromIndex(entityIndex);
  const auto drawComponent = registry_->GetComponent<Drawable>(entity);
  drawComponent.value()->drawable = Text{"Score: " + score, "main", 20};
}

void SceneLeaderboard::UpdateScoreWin(const std::size_t &index, const bool &win) const {
  const auto tags = registry_->GetComponents<Tags>();
  std::size_t entityIndex = 0;

  for (const auto &tag : *tags) {
    if (tag && *tag & ("win_" + std::to_string(index))) {
      break;
    }
    entityIndex++;
  }

  const auto entity = registry_->EntityFromIndex(entityIndex);
  const auto drawComponent = registry_->GetComponent<Drawable>(entity);
  drawComponent.value()->drawable = Text{win ? "State: Win" : "State: Lose", "main", 20};
}
