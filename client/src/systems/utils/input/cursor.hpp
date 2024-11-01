/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** cursor.hpp
*/

#pragma once
#include "core/components/position/position.hpp"
#include "core/components/tags/tags.hpp"
#include "sets/drawable/components/components.hpp"
#include "system_abstract.hpp"

// Here we use a MACRO to define the number of attempts to update the cursor. It's because the cursor
// position depends on the text bounds and the text bounds may be updated after our cursor update.
#define CURSOR_UPDATE_NB_ATTEMPTS 2

namespace rtype::client::systems {
class UtilsInputCursorSystem final
    : public ASystem<core::components::Tags, mew::sets::drawable::Drawable,
                     core::components::Position> {
 public:
  UtilsInputCursorSystem();

  void Run(std::shared_ptr<Registry> r, ComponentsPtr components) override;

 private:
  std::map<std::string, std::size_t> attempts_;
  static void HandleCursor(const std::shared_ptr<Registry>& r, const std::string& tag,
                           const mew::sets::drawable::Drawable& drawable,
                           const core::components::Position& position);

  void CleanAttempts(core::components::Tags* tags, const std::string& tag);
};
}  // namespace rtype::client::systems
