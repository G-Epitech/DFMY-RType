/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** settings.cpp
*/

#include "settings.hpp"

#include "components/drawable.hpp"
#include "components/on_event.hpp"
#include "components/position.hpp"
#include "menu.hpp"
#include "systems/drawable.hpp"
#include "systems/events/mouse/buttons.hpp"
#include "systems/events/mouse/move.hpp"

using namespace rtype::client;

SceneSettings::SceneSettings(const GlobalContext& context) : SceneBase(context) {
  resourcesManager_->LoadFont("assets/fonts/main.ttf", "main");

  registry_->RegisterComponent<components::Position>();
  registry_->RegisterComponent<components::Drawable>();
  registry_->RegisterComponent<components::OnMousePressed>();
  registry_->RegisterComponent<components::OnMouseMoved>();

  registry_->AddSystem<systems::DrawableSystem>(context.windowManager, resourcesManager_);
  registry_->AddSystem<systems::MousePressEventSystem>(context.windowManager);
  registry_->AddSystem<systems::MouseMoveEventSystem>(context.windowManager);
}

void SceneSettings::OnCreate() {
  CreateTitle();
  CreateBackButton();
}

void SceneSettings::OnActivate() {}

void SceneSettings::Update(std::chrono::nanoseconds delta_time) {
  registry_->RunSystems();
}

void SceneSettings::CreateTitle() const {
  const auto title = registry_->SpawnEntity();

  registry_->AddComponent<components::Position>(
      title, {context_.windowManager->width_ / 2, 0 + 150, components::HorizontalAlign::kCenter,
              components::VerticalAlign::kCenter});
  registry_->AddComponent<components::Drawable>(
      title, {components::Text{"Settings", "main", 50}, WindowManager::View::HUD});
}

void SceneSettings::CreateBackButton() const {
  const auto exit_button = registry_->SpawnEntity();

  registry_->AddComponent<components::Position>(
      exit_button, {context_.windowManager->width_ / 2, context_.windowManager->height_ / 2 + 110,
                    components::HorizontalAlign::kCenter, components::VerticalAlign::kCenter});
  registry_->AddComponent<components::Drawable>(
      exit_button, {components::Text{"Back", "main", 20}, WindowManager::View::HUD});
  registry_->AddComponent<components::OnMousePressed>(
      exit_button, components::OnMousePressed{
                       .strategy = events::MouseEventTarget::kLocalTarget,
                       .handler = [this](const sf::Mouse::Button& button, const sf::Vector2f& pos,
                                         const events::MouseEventTarget& target) {
                         if (button == sf::Mouse::Button::Left) {
                           context_.scenesManager->GoToScene<SceneMenu>();
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
