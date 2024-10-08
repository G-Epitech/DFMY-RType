/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** on_key_pressed.hpp
*/

#pragma once

#include "./base.hpp"

namespace rtype::client::systems {
typedef MouseEventSystemBase<events::kMouseReleased, components::OnMouseReleased>
    MouseReleaseEventSystem;
}  // namespace rtype::client::systems
