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
  return registry_.GetComponent<Component>(*this);
}
