/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** menu.cpp
*/

#include "menu.hpp"

#include "components/drawable.hpp"
#include "components/on_event.hpp"
#include "libs/zygarde/src/core/components/components.hpp"
#include "game.hpp"
#include "settings.hpp"
#include "systems/drawable.hpp"
#include "systems/events/mouse/buttons.hpp"
#include "systems/events/mouse/move.hpp"

using namespace rtype::client::scenes;

SceneMenu::SceneMenu(const GlobalContext& context) : SceneBase(context) {
  resourcesManager_->LoadFont("assets/fonts/main.ttf", "main");

  registry_->RegisterComponent<zyc::components::Position>();
  registry_->RegisterComponent<components::Drawable>();
  registry_->RegisterComponent<components::OnMousePressed>();
  registry_->RegisterComponent<components::OnMouseMoved>();

  registry_->AddSystem<systems::DrawableSystem>(context.windowManager, resourcesManager_);
  registry_->AddSystem<systems::MousePressEventSystem>(context.windowManager);
  registry_->AddSystem<systems::MouseMoveEventSystem>(context.windowManager);
}

void SceneMenu::OnCreate() {
  CreateTitle();
  CreatePlayButton();
  CreateSettingsButton();
  CreateExitButton();
}

void SceneMenu::OnActivate() {}

void SceneMenu::Update(std::chrono::nanoseconds delta_time) {
  registry_->RunSystems();
}

void SceneMenu::CreateTitle() const {
  const auto title = registry_->SpawnEntity();
  const auto aligns = zyc::components::Alignment{zyc::components::HorizontalAlign::kCenter,
                                                 zyc::components::VerticalAlign::kCenter};
  const auto point = zyc::types::Vector3f(context_.windowManager->width_ / 2,
                                          context_.windowManager->height_ / 2 - 250);

  registry_->AddComponent<zyc::components::Position>(title, {point, aligns});
  registry_->AddComponent<components::Drawable>(
      title, {components::Text{"R-TYPE", "main", 84}, WindowManager::View::HUD});
}

void SceneMenu::CreatePlayButton() const {
  const auto play_button = registry_->SpawnEntity();
  const auto point =
      zyc::types::Vector3f(context_.windowManager->width_ / 2, context_.windowManager->height_ / 2);
  const auto aligns = zyc::components::Alignment{zyc::components::HorizontalAlign::kCenter,
                                                 zyc::components::VerticalAlign::kCenter};

  registry_->AddComponent<zyc::components::Position>(play_button, {point, aligns});
  registry_->AddComponent<components::Drawable>(
      play_button, {components::Text{"Play", "main", 42}, WindowManager::View::HUD});
  registry_->AddComponent<components::OnMousePressed>(
      play_button, components::OnMousePressed{
                       .strategy = events::MouseEventTarget::kLocalTarget,
                       .handler = [this](const sf::Mouse::Button& button, const sf::Vector2f& pos,
                                         const events::MouseEventTarget& target) {
                         context_.scenesManager->GoToScene<SceneGame>();
                       }});
  registry_->AddComponent<components::OnMouseMoved>(
      play_button, components::OnMouseMoved{
                       .strategy = events::MouseEventTarget::kAnyTarget,
                       .handler = [this, play_button](const sf::Vector2f& pos,
                                                      const events::MouseEventTarget& target) {
                         auto drawables = registry_->GetComponents<components::Drawable>();

                         auto& dr = (*drawables)[static_cast<std::size_t>(play_button)];

                         if (dr) {
                           auto& drawable = dr.value();
                           auto& variant = drawable.drawable;

                           if (std::holds_alternative<components::Text>(variant)) {
                             auto& text = std::get<components::Text>(variant);
                             if (target == events::MouseEventTarget::kLocalTarget) {
                               text.style = sf::Text::Style::Underlined;
                             } else {
                               text.style = sf::Text::Style::Regular;
                             }
                           }
                         }
                       }});
}

void SceneMenu::CreateSettingsButton() const {
  const auto settings_button = registry_->SpawnEntity();
  const auto point = zyc::types::Vector3f(context_.windowManager->width_ / 2,
                                          context_.windowManager->height_ / 2 + 75);
  const auto aligns = zyc::components::Alignment{zyc::components::HorizontalAlign::kCenter,
                                                 zyc::components::VerticalAlign::kCenter};

  registry_->AddComponent<zyc::components::Position>(settings_button, {point, aligns});
  registry_->AddComponent<components::Drawable>(
      settings_button, {components::Text{"Settings", "main", 20}, WindowManager::View::HUD});
  registry_->AddComponent<components::OnMousePressed>(
      settings_button,
      components::OnMousePressed{
          .strategy = events::MouseEventTarget::kLocalTarget,
          .handler = [this](const sf::Mouse::Button& button, const sf::Vector2f& pos,
                            const events::MouseEventTarget& target) {
            if (button == sf::Mouse::Button::Left) {
              context_.scenesManager->GoToScene<SceneSettings>();
            }
          }});
  registry_->AddComponent<components::OnMouseMoved>(
      settings_button,
      components::OnMouseMoved{
          .strategy = events::MouseEventTarget::kAnyTarget,
          .handler = [this, settings_button](const sf::Vector2f& pos,
                                             const events::MouseEventTarget& target) {
            auto drawables = registry_->GetComponents<components::Drawable>();

            auto& dr = (*drawables)[static_cast<std::size_t>(settings_button)];

            if (dr) {
              auto& drawable = dr.value();
              auto& variant = drawable.drawable;

              if (std::holds_alternative<components::Text>(variant)) {
                auto& text = std::get<components::Text>(variant);
                if (target == events::MouseEventTarget::kLocalTarget) {
                  text.style = sf::Text::Style::Underlined;
                } else {
                  text.style = sf::Text::Style::Regular;
                }
              }
            }
          }});
}

void SceneMenu::CreateExitButton() const {
  const auto exit_button = registry_->SpawnEntity();
  const auto point = zyc::types::Vector3f(context_.windowManager->width_ / 2,
                                          context_.windowManager->height_ / 2 + 110);
  const auto aligns = zyc::components::Alignment{zyc::components::HorizontalAlign::kCenter,
                                                 zyc::components::VerticalAlign::kCenter};
  registry_->AddComponent<zyc::components::Position>(exit_button, {point, aligns});
  registry_->AddComponent<components::Drawable>(
      exit_button, {components::Text{"Exit", "main", 20}, WindowManager::View::HUD});
  registry_->AddComponent<components::OnMousePressed>(
      exit_button, components::OnMousePressed{
                       .strategy = events::MouseEventTarget::kLocalTarget,
                       .handler = [this](const sf::Mouse::Button& button, const sf::Vector2f& pos,
                                         events::MouseEventTarget target) {
                         if (button == sf::Mouse::Button::Left) {
                           context_.scenesManager->Quit();
                         }
                       }});
  registry_->AddComponent<components::OnMouseMoved>(
      exit_button, components::OnMouseMoved{
                       .strategy = events::MouseEventTarget::kAnyTarget,
                       .handler = [this, exit_button](const sf::Vector2f& pos,
                                                      const events::MouseEventTarget& target) {
                         auto drawables = registry_->GetComponents<components::Drawable>();

                         auto& dr = (*drawables)[static_cast<std::size_t>(exit_button)];

                         if (dr) {
                           auto& drawable = dr.value();
                           auto& variant = drawable.drawable;

                           if (std::holds_alternative<components::Text>(variant)) {
                             auto& text = std::get<components::Text>(variant);
                             if (target == events::MouseEventTarget::kLocalTarget) {
                               text.style = sf::Text::Style::Underlined;
                             } else {
                               text.style = sf::Text::Style::Regular;
                             }
                           }
                         }
                       }});
}
