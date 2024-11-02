/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** entity.tpp
*/

#pragma once

using namespace zygarde;

template <typename Component>
Component* Entity::GetComponent() {
  auto component = registry_->GetComponent<Component>(*this);
  return component.has_value() ? component.value() : nullptr;
}
