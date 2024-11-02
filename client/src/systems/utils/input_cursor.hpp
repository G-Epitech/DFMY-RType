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

// Here we use a MACRO to define the number of attempts to update the cursor. It's because the
// cursor position depends on the text bounds and the text bounds may be updated after our cursor
// update.
#define CURSOR_UPDATE_NB_ATTEMPTS 2

using namespace zygarde::core::components;
using namespace mew::sets::drawable;

namespace rtype::client::systems::utils::input {
class CursorSystem final : public ASystem<Tags, Drawable, Position> {
 public:
  CursorSystem();

  void Run(std::shared_ptr<Registry> r, ComponentsPtr components) override;

 private:
  /// @brief Map of attempts to update the cursor
  std::map<std::string, std::size_t> attempts_;

  /**
   * @brief Handle the cursor for the input
   * @param r Registry
   * @param tag Tag
   * @param drawable Drawable
   * @param position Position
   */
  static void HandleCursor(const std::shared_ptr<Registry>& r, const std::string& tag,
                           const Drawable& drawable, const Position& position);

  /**
   * @brief Clean the attempts
   * @param tags Tags
   * @param tag Tag
   */
  void CleanAttempts(Tags* tags, const std::string& tag);
};
}  // namespace rtype::client::systems::utils::input
