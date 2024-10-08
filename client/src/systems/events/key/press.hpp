/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** on_key_pressed.hpp
*/

#pragma once

#include "./base.hpp"

namespace rtype::client::systems {
typedef KeyEventSystemBase<events::kKeyReleased, components::OnKeyReleased> KeyReleaseEventSystem;
}  // namespace rtype::client::systems
