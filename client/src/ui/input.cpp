/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** input.cpp
*/

#include "input.hpp"

#include <utility>

#include "constants/settings.hpp"
#include "core/components/tags/tags.hpp"
#include "sets/drawable/components/components.hpp"
#include "sets/events/components/components.hpp"
#include "systems/ui/input_cursor.hpp"

using namespace rtype::client::ui;
using namespace zygarde::core::components;
using namespace mew::sets::drawable;
using namespace mew::sets::events;
using namespace zygarde::core::types;

void Input::Create(const Registry::Ptr& registry, const std::string& tag, const Vector3f position,
                   const Alignment alignment, const unsigned int character_size,
                   const bool disabled) {
  CreateInputField(registry, tag, position, alignment, character_size, disabled);
  CreateBlinkingCursor(registry, tag, position, alignment, character_size, disabled);
}

void Input::CreateInputField(const Registry::Ptr& registry, const std::string& tag,
                             const core::types::Vector3f& position,
                             const core::components::Alignment alignment,
                             const unsigned int character_size, const bool disabled) {
  const auto input_field = registry->SpawnEntity();

  registry->AddComponent<Position>(input_field, {position, alignment});
  registry->AddComponent<Drawable>(input_field,
                                   {Text{"", "main", character_size}, WindowManager::View::HUD});
  Tags tags = Tags({tag, (tag + "_input")});
  if (disabled) {
    tags.AddTag("disabled");
  }
  registry->AddComponent<Tags>(input_field, std::move(tags));
  registry->AddComponent<OnTextEntered>(
      input_field, OnTextEntered{.handler = [registry, input_field](const sf::Uint32& unicode) {
        const auto component = registry->GetComponent<Drawable>(input_field);
        auto entity_tags = registry->GetComponent<Tags>(input_field);
        if (!component || !entity_tags) {
          return;
        }
        if ((*entity_tags) && (*(entity_tags.value()) & "disabled")) {
          return;
        }
        auto& drawable = (*component)->drawable;
        if (!std::holds_alternative<Text>(drawable)) {
          return;
        }
        auto& [text, fontName, characterSize, style, color] = std::get<Text>(drawable);
        if (unicode == '\b') {
          if (!text.empty()) {
            text.pop_back();
          }
        } else if (unicode < ' ' || unicode == 127) {
          return;
        } else {
          text += static_cast<char>(unicode);
        }
        (*entity_tags)->AddTag("input_updated");
      }});
}

void Input::CreateBlinkingCursor(const Registry::Ptr& registry, const std::string& tag,
                                 const core::types::Vector3f& position,
                                 const core::components::Alignment alignment,
                                 const unsigned int character_size, const bool disabled) {
  const auto cursor = registry->SpawnEntity();

  registry->AddComponent<Position>(cursor, {position, alignment});
  registry->AddComponent<Drawable>(cursor,
                                   {Text{"|", "main", character_size}, WindowManager::View::HUD});
  Tags tags = Tags({"blink", tag, (tag + "_cursor")});
  if (disabled) {
    tags.AddTag("disabled");
  }
  registry->AddComponent<Tags>(cursor, std::move(tags));
}
