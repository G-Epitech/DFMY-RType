/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** radio.cpp
*/

#include "radio.hpp"

using namespace rtype::client::components;

Radio::ValueType Radio::Utils::GetValue(const zygarde::tools::sparse_array<Radio>::ptr &radios,
                                        const std::string &id) {
  for (auto &radio : *radios) {
    if (!radio)
      continue;
    if (radio->id == id && radio->selected)
      return radio->value;
  }
  return std::nullopt;
}

Radio::ValueType Radio::Utils::SetValue(const zygarde::tools::sparse_array<Radio>::ptr &radios,
                                        const std::string &id, const Radio::ValueType &value) {
  auto old = GetValue(radios, id);
  auto set = false;
  for (auto &radio : *radios) {
    if (!radio || radio->id != id)
      continue;
    radio->selected = radio->value == value;
    set |= radio->selected;
  }
  if (set) {
    return value;
  } else if (value != std::nullopt && old != std::nullopt) {
    return SetValue(radios, id, old);
  } else {
    return std::nullopt;
  }
}
