/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** input.cpp
*/

#include "input.hpp"

#include "core/components/tags/tags.hpp"
#include "sets/drawable/components/components.hpp"
#include "sets/events/components/components.hpp"

using namespace rtype::client::scenes::utils;
using namespace zygarde::core::components;
using namespace mew::sets::drawable;
using namespace mew::sets::events;
using namespace mew::managers;
using namespace zygarde::core::types;

void Input::Create(const Registry::Ptr& registry, const std::string& tag, const std::string& text,
                   const Vector3f position, const Alignment alignment) {
  CreateInputField(registry, tag, text, position, alignment);
  CreateBlinkingCursor(registry, tag, text, position, alignment);
}

void Input::CreateInputField(Registry::Ptr registry, std::string tag, std::string text,
                             const core::types::Vector3f position,
                             const core::components::Alignment alignment) {
  const auto input_field = registry->SpawnEntity();

  registry->AddComponent<Position>(input_field, {position, alignment});
  registry->AddComponent<Drawable>(input_field, {Text{text, "main", 20}, WindowManager::View::HUD});
  registry->AddComponent<Tags>(input_field, Tags({tag}));
  registry->AddComponent<OnTextEntered>(
      input_field, OnTextEntered{.handler = [registry, input_field](const sf::Uint32& unicode) {
        const auto component = registry->GetComponent<Drawable>(input_field);
        if (!component) {
          return;
        }
        auto& drawable = component->drawable;
        if (!std::holds_alternative<Text>(drawable)) {
          return;
        }
        auto& [text, fontName, characterSize, style, color] = std::get<Text>(drawable);
        if (unicode == 8) {
          if (!text.empty()) {
            text.pop_back();
          }
        } else {
          text += static_cast<char>(unicode);
        }
      }});
}

void Input::CreateBlinkingCursor(Registry::Ptr registry, std::string tag, std::string text,
                                 const core::types::Vector3f position,
                                 const core::components::Alignment alignment) {
  const auto cursor = registry->SpawnEntity();

  registry->AddComponent<Position>(cursor, {position, alignment});
  registry->AddComponent<Drawable>(cursor, {Text{"|", "main", 20}, WindowManager::View::HUD});
  registry->AddComponent<Tags>(cursor, Tags({"blink"}));
  registry->AddComponent<OnTextEntered>(
      cursor, OnTextEntered{.handler = [registry, cursor, tag](const sf::Uint32& unicode) {
        BlinkingCursorFunction(registry, cursor, unicode, tag);
      }});
}

void Input::BlinkingCursorFunction(const Registry::Ptr& registry, const Entity& cursor,
                                   const sf::Uint32& unicode, const std::string& tag) {
  const auto entity_drawable = registry->GetComponent<Drawable>(cursor);
  const auto entity_tags = registry->GetComponent<Tags>(cursor);
  const auto entity_position = registry->GetComponent<Position>(cursor);
  const auto all_tags = registry->GetComponents<Tags>();
  const auto all_drawables = registry->GetComponents<Drawable>();
  const auto all_positions = registry->GetComponents<Position>();

  if (!entity_drawable || !entity_tags || !entity_position || !all_tags || !all_drawables ||
      !all_positions) {
    return;
  }

  const auto begin = all_tags->begin();
  const auto end = all_tags->end();
  std::size_t index = 0;
  for (auto it = begin; it != end; ++it) {
    const auto tags = *it;
    if (!tags) {
      index += 1;
      continue;
    }
    if ((*tags) & tag) {
      if (index >= all_drawables->size() || !(*all_drawables)[index] ||
          index >= all_positions->size() || !(*all_positions)[index]) {
        return;
      }
      auto& input_field_drawable = ((*all_drawables)[index]).value();
      auto& input_field_position = (*all_positions)[index].value();
      if (!std::holds_alternative<Text>(input_field_drawable.drawable)) {
        return;
      }
      auto text = std::get<Text>(input_field_drawable.drawable);
      entity_position->point.x =
          input_field_position.point.x + (input_field_drawable.bounds.width / 2) + 5;
      if (unicode == 8) {
        entity_position->point.x -= text.characterSize;
      }
      entity_tags->AddTag("not_blink");
      entity_drawable->visible = true;
      return;
    }
    index += 1;
  }
}
