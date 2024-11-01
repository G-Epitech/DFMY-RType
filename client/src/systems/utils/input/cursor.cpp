/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** cursor.cpp
*/

#include "cursor.hpp"

#include "core/components/position/position.hpp"

using namespace rtype::client::systems;

UtilsInputCursorSystem::UtilsInputCursorSystem() = default;

void UtilsInputCursorSystem::Run(std::shared_ptr<Registry> r, ComponentsPtr components) {
  for (auto&& [tags, drawable, position] : components) {
    if (!(tags & "input_updated")) {
      continue;
    }
    const auto input_tags = tags.GetTags();
    for (auto& tag : input_tags) {
      if (tag.size() < 6) {
        continue;
      }
      if (tag.substr(tag.size() - 6) != "_input") {
        continue;
      }
      auto tag_name = tag.substr(0, tag.size() - 6);
      HandleCursor(r, tag_name, drawable, position);
      attempts_[tag] += 1;
      CleanAttempts(&tags, tag);
      break;
    }
  }
}

void UtilsInputCursorSystem::HandleCursor(const std::shared_ptr<Registry>& r,
                                          const std::string& tag,
                                          const mew::sets::drawable::Drawable& drawable,
                                          const core::components::Position& position) {
  const auto all_tags = r->GetComponents<zygarde::core::components::Tags>();
  const auto all_positions = r->GetComponents<zygarde::core::components::Position>();
  const auto all_drawables = r->GetComponents<mew::sets::drawable::Drawable>();

  if (!all_tags || !all_positions || !all_drawables) {
    return;
  }

  const auto begin = all_tags->begin();
  const auto end = all_tags->end();
  std::size_t index = 0;

  for (auto it = begin; it != end; ++it) {
    auto& tags = *it;
    if (!tags) {
      index += 1;
      continue;
    }
    if (!(*tags & (tag + "_cursor"))) {
      index += 1;
      continue;
    }

    if (index >= all_drawables->size() || !(*all_drawables)[index] ||
        index >= all_positions->size() || !(*all_positions)[index]) {
      return;
    }
    auto& cursor_drawable = (*all_drawables)[index];
    auto& cursor_position = (*all_positions)[index];
    if (!cursor_drawable || !cursor_position) {
      return;
    }
    cursor_position->point.x = position.point.x + (drawable.bounds.width / 2) - 2;
    tags->AddTag("not_blink");
    cursor_drawable->visible = true;
    break;
  }
}

void UtilsInputCursorSystem::CleanAttempts(core::components::Tags* tags, const std::string& tag) {
  if (attempts_[tag] > CURSOR_UPDATE_NB_ATTEMPTS) {
    tags->RemoveTag("input_updated");
    attempts_[tag] = 0;
  }
}
