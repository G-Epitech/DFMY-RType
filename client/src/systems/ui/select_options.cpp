/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select.cpp
*/

#include "./select_options.hpp"

#include "client/src/ui/select/select.hpp"

using namespace rtype::client::ui;
using namespace rtype::client::systems::ui;

void SelectOptionsSystem::Run(std::shared_ptr<Registry> r, ZippedComponents components) {
  auto containers = r->GetMatchingEntities<SelectContainer>();

  for (auto&& [drawable, position, option] : components) {
    auto container = GetContainer(&containers, option.selectId);
    if (container && container->expanded) {
      UpdateOptionDrawableVisible(r, option, &drawable, *container);
    }
  }
}
void SelectOptionsSystem::UpdateOptionDrawableVisible(const std::shared_ptr<Registry>& r,
                                                      const SelectOption& option,
                                                      Drawable* drawable,
                                                      const SelectContainer& container) {
  if (!drawable || !std::holds_alternative<Rectangle>(drawable->drawable)) {
    return;
  }
  auto& rect = std::get<Rectangle>(drawable->drawable);
  if (option.selected) {
    rect.fillColor = container.selectedColor;
  } else if (option.hovered) {
    rect.fillColor = container.hoveredColor;
  } else {
    rect.fillColor = container.disabledColor;
  }
}

SelectContainer* SelectOptionsSystem::GetContainer(zipper<SelectContainer>* containers,
                                                   const std::string& selectId) {
  for (auto&& [container] : *containers) {
    if (container.selectId == selectId) {
      return &container;
    }
  }
  return nullptr;
}
