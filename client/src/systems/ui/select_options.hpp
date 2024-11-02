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

class SelectOptionsSystem final : public ASystem<Drawable, Position, SelectOption> {
 public:
  SelectOptionsSystem() = default;

  void Run(std::shared_ptr<Registry> r, ZippedComponents components) override;

 private:
  /**
   * @brief Update the options state
   * @param r Registry
   * @param option Option to update
   * @param container Container of the option
   */
  static void UpdateOptionDrawableVisible(const std::shared_ptr<Registry> &r,
                                          const SelectOption &option, Drawable *drawable,
                                          const SelectContainer &container);

  /**
   * @brief Get the container
   * @param containers Containers
   * @param selectId Select id
   * @return Container if found, nullptr otherwise
   */
  static SelectContainer *GetContainer(zipper<SelectContainer> *containers,
                                       const std::string &selectId);
};
}  // namespace rtype::client::systems::ui
