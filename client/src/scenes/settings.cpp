/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** settings.cpp
*/

#include "settings.hpp"

#include "client/src/constants/settings.hpp"
#include "components/radio.hpp"
#include "libs/mew/src/sets/drawable/drawable.hpp"
#include "libs/mew/src/sets/events/events.hpp"
#include "menu.hpp"

using namespace rtype::client;
using namespace rtype::client::components;
using namespace rtype::client::scenes;
using namespace mew::sets::events;
using namespace mew::sets::drawable;
using namespace mew::managers;
using namespace zygarde::core::components;
using namespace zygarde::core::types;
using namespace porygon;

SceneSettings::SceneSettings(DependenciesHandler::Ptr services) : SceneBase(std::move(services)) {
  settingsManager_ = services_->Get<SettingsManager>();

  managers_.resources->LoadTexture("assets/ui/menu.png", "menu");
  managers_.sound->LoadSoundBuffer("assets/sounds/button_click.ogg", "buttons:click");

  registry_->RegisterComponent<Radio>();
}

void SceneSettings::OnCreate() {
  constexpr auto left = 600;
  const auto right = managers_.window->width_ - 600;

  CreateTitle();
  CreateBackButton();
  CreateFullscreenLabel(left, 250);
  CreateFullscreenButton(right, 250);
  CreateDisableSoundsButton(right, 300);
  CreateDisableSoundsLabel(left, 300);
  CreateDisableMusicButton(right, 350);
  CreateDisableMusicLabel(left, 350);
  CreateDisableAnimationsButton(right, 400);
  CreateDisableAnimationsLabel(left, 400);
  CreateColorBlindnessSetting(left, 450);
  CreateKeyMapSetting(left, 550);
  CreateMainEntity();
}

void SceneSettings::OnActivate() {}

void SceneSettings::Update(std::chrono::nanoseconds delta_time) {
  registry_->RunSystems();

  auto blindness_mode =
      Radio::Utils::GetValue(registry_->GetComponents<Radio>(), "color_blindness");
  if (blindness_mode && blindness_mode.has_value()) {
    managers_.window->SetShader(std::get<std::string>(blindness_mode.value()));
  }

  auto keymap_mode = Radio::Utils::GetValue(registry_->GetComponents<Radio>(), "keymap");
  if (keymap_mode && keymap_mode.has_value()) {
    auto mode = std::get<std::string>(keymap_mode.value());
    if (mode == "zqsd") {
      settingsManager_->Set(SETTING_GAME_KEYMAP, KeyMap::ZQSD);
    } else {
      settingsManager_->Set(SETTING_GAME_KEYMAP, KeyMap::Arrows);
    }
  }
}

void SceneSettings::CreateMainEntity() const {
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

void SceneSettings::CreateTitle() const {
  const auto title = registry_->SpawnEntity();
  const auto point = Vector3f(managers_.window->width_ / 2, 150);
  const auto aligns = Alignment{HorizontalAlign::kCenter, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(title, {point, aligns});
  registry_->AddComponent<Drawable>(title,
                                    {Text{"Settings", "main", 50}, WindowManager::View::HUD});
}

void SceneSettings::CreateBackButton() const {
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

void SceneSettings::CreateFullscreenButton(const float &x, const float &y) const {
  const auto fullscreen_button = registry_->SpawnEntity();
  const sf::IntRect disable{192, 68, 16, 8};
  const sf::IntRect active{224, 68, 16, 8};
  const auto window_style = managers_.window->GetStyle();
  const auto point = Vector3f(x, y);
  const auto aligns = Alignment{HorizontalAlign::kRight, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(fullscreen_button, {point, aligns});
  registry_->AddComponent<Drawable>(
      fullscreen_button, {Texture{"menu", 4, window_style == sf::Style::Default ? disable : active},
                          WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      fullscreen_button,
      OnMousePressed{.strategy = MouseEventTarget::kLocalTarget,
                     .handler = [this, disable, active, fullscreen_button](
                                    const sf::Mouse::Button &button, const sf::Vector2f &pos,
                                    const MouseEventTarget &target) {
                       if (button == sf::Mouse::Button::Left) {
                         const auto windowStyle = managers_.window->GetStyle();
                         if (windowStyle == sf::Style::Default) {
                           managers_.window->SetStyle(sf::Style::Fullscreen);
                         } else {
                           managers_.window->SetStyle(sf::Style::Default);
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
  const auto point = Vector3f(x, y);
  const auto aligns = Alignment{HorizontalAlign::kLeft, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(fullscreen_label, {point, aligns});
  registry_->AddComponent<Drawable>(fullscreen_label,
                                    {Text{"Fullscreen", "main", 20}, WindowManager::View::HUD});
}

void SceneSettings::CreateDisableSoundsButton(const float &x, const float &y) const {
  const auto volume_button = registry_->SpawnEntity();
  const sf::IntRect disable{192, 68, 16, 8};
  const sf::IntRect active{224, 68, 16, 8};
  const auto soundVolume = managers_.sound->GetSoundVolume();
  const auto point = Vector3f(x, y);
  const auto aligns = Alignment{HorizontalAlign::kRight, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(volume_button, {point, aligns});
  registry_->AddComponent<Drawable>(
      volume_button,
      {Texture{"menu", 4, soundVolume > 0 ? active : disable}, WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      volume_button,
      OnMousePressed{.strategy = MouseEventTarget::kLocalTarget,
                     .handler = [this, disable, active, volume_button](
                                    const sf::Mouse::Button &button, const sf::Vector2f &pos,
                                    const MouseEventTarget &target) {
                       if (button == sf::Mouse::Button::Left) {
                         const auto soundVolume = managers_.sound->GetSoundVolume();
                         if (soundVolume > 0) {
                           managers_.sound->SetSoundVolume(0);
                         } else {
                           managers_.sound->SetSoundVolume(100);
                         }
                         auto drawables = registry_->GetComponents<Drawable>();
                         auto &dr = (*drawables)[static_cast<std::size_t>(volume_button)];

                         if (dr) {
                           auto &drawable = dr.value();
                           auto &variant = drawable.drawable;

                           if (std::holds_alternative<Texture>(variant)) {
                             auto &texture = std::get<Texture>(variant);
                             texture.rect = soundVolume > 0 ? disable : active;
                           }
                         }
                       }
                     }});
}

void SceneSettings::CreateDisableSoundsLabel(const float &x, const float &y) const {
  const auto volume_label = registry_->SpawnEntity();
  const auto point = Vector3f(x, y);
  const auto aligns = Alignment{HorizontalAlign::kLeft, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(volume_label, {point, aligns});
  registry_->AddComponent<Drawable>(volume_label,
                                    {Text{"Sounds", "main", 20}, WindowManager::View::HUD});
}

void SceneSettings::CreateDisableMusicButton(const float &x, const float &y) const {
  const auto music_button = registry_->SpawnEntity();
  const sf::IntRect disable{192, 68, 16, 8};
  const sf::IntRect active{224, 68, 16, 8};
  const auto soundVolume = managers_.sound->GetSoundVolume();
  const auto point = Vector3f(x, y);
  const auto aligns = Alignment{HorizontalAlign::kRight, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(music_button, {point, aligns});
  registry_->AddComponent<Drawable>(
      music_button,
      {Texture{"menu", 4, soundVolume > 0 ? active : disable}, WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      music_button,
      OnMousePressed{.strategy = MouseEventTarget::kLocalTarget,
                     .handler = [this, disable, active, music_button](
                                    const sf::Mouse::Button &button, const sf::Vector2f &pos,
                                    const MouseEventTarget &target) {
                       if (button == sf::Mouse::Button::Left) {
                         const auto musicVolume = managers_.sound->GetMusicVolume();
                         if (musicVolume > 0) {
                           managers_.sound->SetMusicVolume(0);
                         } else {
                           managers_.sound->SetMusicVolume(100);
                         }
                         auto drawables = registry_->GetComponents<Drawable>();
                         auto &dr = (*drawables)[static_cast<std::size_t>(music_button)];

                         if (dr) {
                           auto &drawable = dr.value();
                           auto &variant = drawable.drawable;

                           if (std::holds_alternative<Texture>(variant)) {
                             auto &texture = std::get<Texture>(variant);
                             texture.rect = musicVolume > 0 ? disable : active;
                           }
                         }
                       }
                     }});
}

void SceneSettings::CreateDisableMusicLabel(const float &x, const float &y) const {
  const auto volume_label = registry_->SpawnEntity();
  const auto point = Vector3f(x, y);
  const auto aligns = Alignment{HorizontalAlign::kLeft, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(volume_label, {point, aligns});
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

void SceneSettings::CreateColorBlindnessLabel(const float &x, const float &y) const {
  const auto label = registry_->SpawnEntity();
  const auto point = Vector3f(x, y);
  const auto aligns = Alignment{HorizontalAlign::kLeft, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(label, {point, aligns});
  registry_->AddComponent<Drawable>(label,
                                    {Text{"Color settings", "main", 20}, WindowManager::View::HUD});
}

void SceneSettings::CreateColorBlindnessRadioOption(const std::string &label,
                                                    const std::string &value,
                                                    const zygarde::core::types::Vector2f &pos) {
  auto label_entity = registry_->SpawnEntity();
  auto radio_entity = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kLeft, VerticalAlign::kCenter};
  auto on_mouse_pressed = [this, radio_entity, value](const sf::Mouse::Button &button,
                                                      const sf::Vector2f &pos,
                                                      const MouseEventTarget &target) {
    if (button == sf::Mouse::Button::Left) {
      SelectColorBlindnessRadioOptions(value);
    }
  };

  registry_->AddComponent<Position>(radio_entity, {Vector3f(pos.x, pos.y), aligns});
  registry_->AddComponent<Drawable>(radio_entity, {Texture{"menu", 2.5}, WindowManager::View::HUD});

  registry_->AddComponent<Radio>(radio_entity, {.id = "color_blindness", .value = value});
  registry_->AddComponent<OnMousePressed>(
      radio_entity, {.strategy = MouseEventTarget::kLocalTarget, .handler = on_mouse_pressed});
  registry_->AddComponent<Position>(label_entity, {Vector3f(pos.x + 50, pos.y), aligns});
  registry_->AddComponent<Drawable>(label_entity,
                                    {Text{label, "main", 13}, WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      label_entity, {.strategy = MouseEventTarget::kLocalTarget, .handler = on_mouse_pressed});
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

void SceneSettings::CreateDisableAnimationsButton(const float &x, const float &y) const {
  const auto music_button = registry_->SpawnEntity();
  const sf::IntRect disable{192, 68, 16, 8};
  const sf::IntRect active{224, 68, 16, 8};
  const auto animationStatus = settingsManager_->Get<bool>(SETTING_GAME_ANIMATIONS);
  const auto point = Vector3f(x, y);
  const auto aligns = Alignment{HorizontalAlign::kRight, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(music_button, {point, aligns});
  registry_->AddComponent<Drawable>(
      music_button,
      {Texture{"menu", 4, animationStatus ? active : disable}, WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      music_button,
      OnMousePressed{.strategy = MouseEventTarget::kLocalTarget,
                     .handler = [this, disable, active, music_button](
                                    const sf::Mouse::Button &button, const sf::Vector2f &pos,
                                    const MouseEventTarget &target) {
                       if (button == sf::Mouse::Button::Left) {
                         const auto animations =
                             settingsManager_->Get<bool>(SETTING_GAME_ANIMATIONS);
                         settingsManager_->Set(SETTING_GAME_ANIMATIONS, !animations);
                         auto drawables = registry_->GetComponents<Drawable>();
                         auto &dr = (*drawables)[static_cast<std::size_t>(music_button)];

                         if (dr) {
                           auto &drawable = dr.value();
                           auto &variant = drawable.drawable;

                           if (std::holds_alternative<Texture>(variant)) {
                             auto &texture = std::get<Texture>(variant);
                             texture.rect = animations ? disable : active;
                           }
                         }
                       }
                     }});
}

void SceneSettings::CreateDisableAnimationsLabel(const float &x, const float &y) const {
  const auto volume_label = registry_->SpawnEntity();
  const auto point = Vector3f(x, y);
  const auto aligns = Alignment{HorizontalAlign::kLeft, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(volume_label, {point, aligns});
  registry_->AddComponent<Drawable>(volume_label,
                                    {Text{"Animations", "main", 20}, WindowManager::View::HUD});
}
void SceneSettings::CreateKeyMapLabel(const float &x, const float &y) const {
  const auto volume_label = registry_->SpawnEntity();
  const auto point = Vector3f(x, y);
  const auto aligns = Alignment{HorizontalAlign::kLeft, VerticalAlign::kCenter};

  registry_->AddComponent<Position>(volume_label, {point, aligns});
  registry_->AddComponent<Drawable>(volume_label,
                                    {Text{"Keymap", "main", 20}, WindowManager::View::HUD});
}

void SceneSettings::CreateKeyMapSetting(const float &x, const float &y) {
  CreateKeyMapLabel(x, y);
  CreateKeyMapRadioOption("ZQSD mode", "zqsd", {x + 50, y + 40});
  CreateKeyMapRadioOption("Arrow mode", "arrow", {x + 400, y + 40});
  SelectKeyMapRadioOptions("zqsd");
}

void SceneSettings::CreateKeyMapRadioOption(const std::string &label, const std::string &value,
                                            const zygarde::core::types::Vector2f &position) {
  auto label_entity = registry_->SpawnEntity();
  auto radio_entity = registry_->SpawnEntity();
  const auto aligns = Alignment{HorizontalAlign::kLeft, VerticalAlign::kCenter};
  auto on_mouse_pressed = [this, radio_entity, value](const sf::Mouse::Button &button,
                                                      const sf::Vector2f &pos,
                                                      const MouseEventTarget &target) {
    if (button == sf::Mouse::Button::Left) {
      SelectKeyMapRadioOptions(value);
    }
  };

  registry_->AddComponent<Position>(radio_entity, {Vector3f(position.x, position.y), aligns});
  registry_->AddComponent<Drawable>(radio_entity, {Texture{"menu", 2.5}, WindowManager::View::HUD});

  registry_->AddComponent<Radio>(radio_entity, {.id = "keymap", .value = value});
  registry_->AddComponent<OnMousePressed>(
      radio_entity, {.strategy = MouseEventTarget::kLocalTarget, .handler = on_mouse_pressed});
  registry_->AddComponent<Position>(label_entity, {Vector3f(position.x + 50, position.y), aligns});
  registry_->AddComponent<Drawable>(label_entity,
                                    {Text{label, "main", 13}, WindowManager::View::HUD});
  registry_->AddComponent<OnMousePressed>(
      label_entity, {.strategy = MouseEventTarget::kLocalTarget, .handler = on_mouse_pressed});
}

void SceneSettings::SelectKeyMapRadioOptions(const std::string &selected_value) {
  static const sf::IntRect disable{192, 68, 16, 8};
  static const sf::IntRect active{224, 68, 16, 8};
  auto radio_components = registry_->GetComponents<Radio>();
  auto drawables = registry_->GetComponents<Drawable>();
  std::size_t entity_id = 0;

  for (auto &radio : *radio_components) {
    if (!radio || (*radio).id != "keymap") {
      entity_id += 1;
      continue;
    }
    auto &drawable = (*drawables)[entity_id];
    auto &variant = drawable->drawable;
    auto selected =
        radio->value.has_value() && std::get<std::string>(*(radio->value)) == selected_value;
    auto &texture = std::get<Texture>(variant);
    texture.rect = selected ? active : disable;
    radio->selected = selected;
    entity_id += 1;
  }
}
