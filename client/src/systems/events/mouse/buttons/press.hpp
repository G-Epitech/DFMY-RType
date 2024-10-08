/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** on_key_pressed.hpp
*/

#pragma once

#include "./base.hpp"
#include "components/position.hpp"
#include "src/systems/events/base.hpp"
#include "window/window_manager.hpp"

namespace rtype::client::systems {
typedef MouseEventSystemBase<events::kMousePressed, components::OnMousePressed>
    MousePressEventSystem;
}  // namespace rtype::client::systems
