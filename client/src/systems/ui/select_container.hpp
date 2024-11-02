/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select.hpp
*/

#pragma once

#include "client/src/components/ui/select.hpp"
#include "libs/mew/src/sets/drawable/components/components.hpp"
#include "libs/zygarde/src/core/components/position/position.hpp"
#include "libs/zygarde/src/core/components/tags/tags.hpp"
#include "libs/zygarde/src/system_abstract.hpp"

namespace rtype::client::systems::ui {
using namespace zygarde::core::components;
using namespace mew::sets::drawable;
using namespace rtype::client::components;

class SelectContainerSystem final : public ASystem<Drawable, Position, SelectContainer> {
 public:
  SelectContainerSystem() = default;

  void Run(std::shared_ptr<Registry> r, ZippedComponents components) override;

 private:
  /**
   * @brief Update the options state
   * @param r Registry
   * @param container Select container
   * @param new_label New label
   */
  static void UpdateOptionsState(const std::shared_ptr<Registry>& r,
                                 const SelectContainer& container, std::string* new_label);

  /**
   * @brief Update the container label
   * @param r Registry
   * @param container Container to update
   * @param new_label New label to set
   */
  static void UpdateContainerLabel(const std::shared_ptr<Registry>& r,
                                   const SelectContainer& container, const std::string& new_label);

  /**
   * Update the option
   * @param container Container of the option
   * @param option Option to update
   * @param drawable Drawable of the option
   */
  static void UpdateOption(const SelectContainer& container, SelectOption* option,
                           Drawable* drawable);

  /**
   * @brief Update the options text visibility
   * @param r Registry
   * @param container Container to update

   */
  static void UpdateOptionsVisibility(const std::shared_ptr<Registry>& r,
                                      const SelectContainer& container);
};
}  // namespace rtype::client::systems::ui
