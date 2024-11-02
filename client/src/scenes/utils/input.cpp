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
#include "systems/utils/input_cursor.hpp"

using namespace rtype::client::scenes::utils;
using namespace zygarde::core::components;
using namespace mew::sets::drawable;
using namespace mew::sets::events;
using namespace mew::managers;
using namespace zygarde::core::types;

void Input::Create(const Registry::Ptr& registry, const std::string& tag, const Vector3f position,
                   const Alignment alignment) {
  CreateInputField(registry, tag, position, alignment);
  CreateBlinkingCursor(registry, tag, position, alignment);
}

void Input::CreateInputField(const Registry::Ptr& registry, std::string tag,
                             const core::types::Vector3f position,
                             const core::components::Alignment alignment) {
  const auto input_field = registry->SpawnEntity();

  registry->AddComponent<Position>(input_field, {position, alignment});
  registry->AddComponent<Drawable>(input_field, {Text{"", "main", 20}, WindowManager::View::HUD});
  registry->AddComponent<Tags>(input_field, Tags({tag, (tag + "_input")}));
  registry->AddComponent<OnTextEntered>(
      input_field, OnTextEntered{.handler = [registry, input_field](const sf::Uint32& unicode) {
        const auto component = registry->GetComponent<Drawable>(input_field);
        const auto entity_tags = registry->GetComponent<Tags>(input_field);
        if (!component || !entity_tags) {
          return;
        }
        auto& drawable = (*component)->drawable;
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
        (*entity_tags)->AddTag("input_updated");
      }});
}

void Input::CreateBlinkingCursor(const Registry::Ptr& registry, const std::string& tag,
                                 const core::types::Vector3f position,
                                 const core::components::Alignment alignment) {
  const auto cursor = registry->SpawnEntity();

  registry->AddComponent<Position>(cursor, {position, alignment});
  registry->AddComponent<Drawable>(cursor, {Text{"|", "main", 20}, WindowManager::View::HUD});
  registry->AddComponent<Tags>(cursor, Tags({"blink", (tag + "_cursor")}));
}
