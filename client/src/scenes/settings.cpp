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
#include "components/radio.hpp"
#include "menu.hpp"
#include "systems/drawable.hpp"
#include "systems/events/mouse/buttons.hpp"
#include "systems/events/mouse/move.hpp"

using namespace rtype::client;
using namespace rtype::client::components;
using namespace rtype::client::scenes;

SceneSettings::SceneSettings(const GlobalContext &context) : SceneBase(context) {
  resourcesManager_->LoadFont("assets/fonts/main.ttf", "main");
  resourcesManager_->LoadTexture("assets/ui/menu.png", "menu");

  soundManager_->LoadSoundBuffer("assets/sounds/button_click.ogg", "button_click");

  registry_->RegisterComponent<Position>();
  registry_->RegisterComponent<Drawable>();
  registry_->RegisterComponent<OnMousePressed>();
  registry_->RegisterComponent<OnMouseMoved>();
  registry_->RegisterComponent<Radio>();

  registry_->AddSystem<systems::MousePressEventSystem>(context.windowManager);
  registry_->AddSystem<systems::MouseMoveEventSystem>(context.windowManager);
  registry_->AddSystem<systems::DrawableSystem>(context.windowManager, resourcesManager_);
}

void SceneSettings::OnCreate() {
  constexpr auto left = 600;
  const auto right = context_.windowManager->width_ - 600;

  CreateTitle();
  CreateBackButton();
  CreateFullscreenLabel(left, 250);
  CreateFullscreenButton(right, 250);
  CreateDisableSoundsButton(right, 300);
  CreateDisableSoundsLabel(left, 300);
  CreateDisableMusicButton(right, 350);
  CreateDisableMusicLabel(left, 350);
  CreateMainEntity();
  CreateColorBlindnessSetting(left, 400);
}

void SceneSettings::OnActivate() {}

void SceneSettings::Update(std::chrono::nanoseconds delta_time) {
  registry_->RunSystems();
  auto v = Radio::Utils::GetValue(registry_->GetComponents<Radio>(), "color_blindness");
  if (v && v.has_value()) {
    context_.windowManager->SetShader(std::get<std::string>(v.value()));
  }
}

void SceneSettings::CreateMainEntity() const {
  const auto main = registry_->SpawnEntity();

  registry_->AddComponent<OnMousePressed>(
      main,
      OnMousePressed{.strategy = events::MouseEventTarget::kAnyTarget,
                     .handler = [this](const sf::Mouse::Button &button, const sf::Vector2f &pos,
                                       const events::MouseEventTarget &target) {
                       if (button == sf::Mouse::Button::Left) {
                         soundManager_->PlaySound("button_click");
                       }
                     }});
}

void SceneSettings::CreateTitle() const {
  const auto title = registry_->SpawnEntity();

  registry_->AddComponent<Position>(title, {context_.windowManager->width_ / 2, 0 + 150,
                                            HorizontalAlign::kCenter, VerticalAlign::kCenter});
  registry_->AddComponent<Drawable>(title,
                                    {Text{"Settings", "main", 50}, WindowManager::View::HUD});
}

void SceneSettings::CreateBackButton() const {
  const auto exit_button = registry_->SpawnEntity();

  registry_->AddComponent<Position>(
      exit_button, {context_.windowManager->width_ / 2, context_.windowManager->height_ - 50,
                    HorizontalAlign::kCenter, VerticalAlign::kCenter});
  registry_->AddComponent<Drawable>(exit_button,
                                    {Text{"Back", "main", 20}, WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      exit_button,
      OnMousePressed{.strategy = events::MouseEventTarget::kLocalTarget,
                     .handler = [this](const sf::Mouse::Button &button, const sf::Vector2f &pos,
                                       const events::MouseEventTarget &target) {
                       if (button == sf::Mouse::Button::Left) {
                         context_.scenesManager->GoToScene<SceneMenu>();
                       }
                     }});
  registry_->AddComponent<OnMouseMoved>(
      exit_button,
      OnMouseMoved{.strategy = events::MouseEventTarget::kAnyTarget,
                   .handler = [this, exit_button](const sf::Vector2f &pos,
                                                  const events::MouseEventTarget &target) {
                     auto drawables = registry_->GetComponents<Drawable>();

                     auto &dr = (*drawables)[static_cast<std::size_t>(exit_button)];

                     if (dr) {
                       auto &drawable = dr.value();
                       auto &variant = drawable.drawable;

                       if (std::holds_alternative<Text>(variant)) {
                         auto &text = std::get<Text>(variant);
                         if (target == events::MouseEventTarget::kLocalTarget) {
                           text.style = sf::Text::Style::Underlined;
                         } else {
                           text.style = sf::Text::Style::Regular;
                         }
                       }
                     }
                   }});
}

void SceneSettings::CreateFullscreenButton(const float &x, const float &y) const {
  const auto fullscreen_button = registry_->SpawnEntity();
  const sf::IntRect disable{192, 68, 16, 8};
  const sf::IntRect active{224, 68, 16, 8};
  const auto window_style = context_.windowManager->GetStyle();

  registry_->AddComponent<Position>(fullscreen_button,
                                    {x, y, HorizontalAlign::kRight, VerticalAlign::kCenter});
  registry_->AddComponent<Drawable>(
      fullscreen_button, {Texture{"menu", 4, window_style == sf::Style::Default ? disable : active},
                          WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      fullscreen_button,
      OnMousePressed{.strategy = events::MouseEventTarget::kLocalTarget,
                     .handler = [this, disable, active, fullscreen_button](
                                    const sf::Mouse::Button &button, const sf::Vector2f &pos,
                                    const events::MouseEventTarget &target) {
                       if (button == sf::Mouse::Button::Left) {
                         const auto windowStyle = context_.windowManager->GetStyle();
                         if (windowStyle == sf::Style::Default) {
                           context_.windowManager->SetStyle(sf::Style::Fullscreen);
                         } else {
                           context_.windowManager->SetStyle(sf::Style::Default);
                         }
                         auto drawables = registry_->GetComponents<Drawable>();
                         auto &dr = (*drawables)[static_cast<std::size_t>(fullscreen_button)];

                         if (dr) {
                           auto &drawable = dr.value();
                           auto &variant = drawable.drawable;

                           if (std::holds_alternative<Texture>(variant)) {
                             auto &texture = std::get<Texture>(variant);
                             texture.rect = windowStyle == sf::Style::Default ? active : disable;
                           }
                         }
                       }
                     }});
}

void SceneSettings::CreateFullscreenLabel(const float &x, const float &y) const {
  const auto fullscreen_label = registry_->SpawnEntity();

  registry_->AddComponent<Position>(fullscreen_label,
                                    {x, y, HorizontalAlign::kLeft, VerticalAlign::kCenter});
  registry_->AddComponent<Drawable>(fullscreen_label,
                                    {Text{"Fullscreen", "main", 20}, WindowManager::View::HUD});
}

void SceneSettings::CreateDisableSoundsButton(const float &x, const float &y) const {
  const auto volume_button = registry_->SpawnEntity();
  const sf::IntRect disable{192, 68, 16, 8};
  const sf::IntRect active{224, 68, 16, 8};
  const auto soundVolume = soundManager_->GetSoundVolume();

  registry_->AddComponent<components::Position>(
      volume_button,
      {x, y, components::HorizontalAlign::kRight, components::VerticalAlign::kCenter});
  registry_->AddComponent<components::Drawable>(
      volume_button, {components::Texture{"menu", 4, soundVolume > 0 ? active : disable},
                      WindowManager::View::HUD});
  registry_->AddComponent<components::OnMousePressed>(
      volume_button, components::OnMousePressed{
                         .strategy = events::MouseEventTarget::kLocalTarget,
                         .handler = [this, disable, active, volume_button](
                                        const sf::Mouse::Button &button, const sf::Vector2f &pos,
                                        const events::MouseEventTarget &target) {
                           if (button == sf::Mouse::Button::Left) {
                             const auto soundVolume = soundManager_->GetSoundVolume();
                             if (soundVolume > 0) {
                               soundManager_->SetSoundVolume(0);
                             } else {
                               soundManager_->SetSoundVolume(100);
                             }
                             auto drawables = registry_->GetComponents<components::Drawable>();
                             auto &dr = (*drawables)[static_cast<std::size_t>(volume_button)];

                             if (dr) {
                               auto &drawable = dr.value();
                               auto &variant = drawable.drawable;

                               if (std::holds_alternative<components::Texture>(variant)) {
                                 auto &texture = std::get<components::Texture>(variant);
                                 texture.rect = soundVolume > 0 ? disable : active;
                               }
                             }
                           }
                         }});
}

void SceneSettings::CreateDisableSoundsLabel(const float &x, const float &y) const {
  const auto volume_label = registry_->SpawnEntity();

  registry_->AddComponent<Position>(volume_label,
                                    {x, y, HorizontalAlign::kLeft, VerticalAlign::kCenter});
  registry_->AddComponent<Drawable>(volume_label,
                                    {Text{"Sounds", "main", 20}, WindowManager::View::HUD});
}

void SceneSettings::CreateDisableMusicButton(const float &x, const float &y) const {
  const auto music_button = registry_->SpawnEntity();
  const sf::IntRect disable{192, 68, 16, 8};
  const sf::IntRect active{224, 68, 16, 8};
  const auto soundVolume = soundManager_->GetSoundVolume();

  registry_->AddComponent<components::Position>(
      music_button,
      {x, y, components::HorizontalAlign::kRight, components::VerticalAlign::kCenter});
  registry_->AddComponent<components::Drawable>(
      music_button, {components::Texture{"menu", 4, soundVolume > 0 ? active : disable},
                     WindowManager::View::HUD});
  registry_->AddComponent<components::OnMousePressed>(
      music_button, components::OnMousePressed{
                        .strategy = events::MouseEventTarget::kLocalTarget,
                        .handler = [this, disable, active, music_button](
                                       const sf::Mouse::Button &button, const sf::Vector2f &pos,
                                       const events::MouseEventTarget &target) {
                          if (button == sf::Mouse::Button::Left) {
                            const auto musicVolume = soundManager_->GetMusicVolume();
                            if (musicVolume > 0) {
                              soundManager_->SetMusicVolume(0);
                            } else {
                              soundManager_->SetMusicVolume(100);
                            }
                            auto drawables = registry_->GetComponents<components::Drawable>();
                            auto &dr = (*drawables)[static_cast<std::size_t>(music_button)];

                            if (dr) {
                              auto &drawable = dr.value();
                              auto &variant = drawable.drawable;

                              if (std::holds_alternative<components::Texture>(variant)) {
                                auto &texture = std::get<components::Texture>(variant);
                                texture.rect = musicVolume > 0 ? disable : active;
                              }
                            }
                          }
                        }});
}

void SceneSettings::CreateDisableMusicLabel(const float &x, const float &y) const {
  const auto volume_label = registry_->SpawnEntity();

  registry_->AddComponent<Position>(volume_label,
                                    {x, y, HorizontalAlign::kLeft, VerticalAlign::kCenter});
  registry_->AddComponent<Drawable>(volume_label,
                                    {Text{"Music", "main", 20}, WindowManager::View::HUD});
}

void SceneSettings::CreateColorBlindnessSetting(const float &x, const float &y) {
  CreateColorBlindnessLabel(x, y);
  CreateColorBlindnessRadioOption("Normal", "normal", {x + 50, y + 40});
  CreateColorBlindnessRadioOption("Protanopia", "protanopia", {x + 50, y + 65});
  CreateColorBlindnessRadioOption("Deuteranopia", "deuteranopia", {x + 400, y + 40});
  CreateColorBlindnessRadioOption("Tritanopia", "tritanopia", {x + 400, y + 65});
  SelectColorBlindnessRadioOptions("normal");
}

void SceneSettings::CreateColorBlindnessLabel(const float &x, const float &y) {
  const auto label = registry_->SpawnEntity();

  registry_->AddComponent<Position>(label, {x, y, HorizontalAlign::kLeft, VerticalAlign::kCenter});
  registry_->AddComponent<Drawable>(label,
                                    {Text{"Color settings", "main", 20}, WindowManager::View::HUD});
}

void SceneSettings::CreateColorBlindnessRadioOption(
    const std::string &label, const std::string &value,
    const zygarde::core::types::Vector2f &position) {
  auto label_entity = registry_->SpawnEntity();
  auto radio_entity = registry_->SpawnEntity();
  auto on_mouse_pressed = [this, radio_entity, value](const sf::Mouse::Button &button,
                                                      const sf::Vector2f &pos,
                                                      const events::MouseEventTarget &target) {
    if (button == sf::Mouse::Button::Left) {
      SelectColorBlindnessRadioOptions(value);
    }
  };

  registry_->AddComponent<Position>(
      radio_entity, {position.x, position.y, HorizontalAlign::kLeft, VerticalAlign::kCenter});
  registry_->AddComponent<Drawable>(radio_entity, {Texture{"menu", 2.5}, WindowManager::View::HUD});

  registry_->AddComponent<Radio>(radio_entity, {.id = "color_blindness", .value = value});
  registry_->AddComponent<OnMousePressed>(
      radio_entity,
      {.strategy = events::MouseEventTarget::kLocalTarget, .handler = on_mouse_pressed});
  registry_->AddComponent<Position>(
      label_entity, {position.x + 50, position.y, HorizontalAlign::kLeft, VerticalAlign::kCenter});
  registry_->AddComponent<Drawable>(label_entity,
                                    {Text{label, "main", 13}, WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      label_entity,
      {.strategy = events::MouseEventTarget::kLocalTarget, .handler = on_mouse_pressed});
}

void SceneSettings::SelectColorBlindnessRadioOptions(const std::string &value) {
  static const sf::IntRect disable{192, 68, 16, 8};
  static const sf::IntRect active{224, 68, 16, 8};
  auto radio_components = registry_->GetComponents<Radio>();
  auto drawables = registry_->GetComponents<Drawable>();
  std::size_t entity_id = 0;

  for (auto &radio : *radio_components) {
    if (!radio || (*radio).id != "color_blindness") {
      entity_id += 1;
      continue;
    }
    auto &drawable = (*drawables)[entity_id];
    auto &variant = drawable->drawable;
    auto selected = radio->value.has_value() && std::get<std::string>(*(radio->value)) == value;
    auto &texture = std::get<Texture>(variant);
    texture.rect = selected ? active : disable;
    radio->selected = selected;
    entity_id += 1;
  }
}
