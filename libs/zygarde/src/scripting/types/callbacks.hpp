/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** callbacks.hpp
*/

#pragma once

#include <any>
#include <functional>
#include <map>
#include <memory>
#include <string>

#include "context.hpp"
#include "physics/2d/types/collision_2d.hpp"
#include "registry.hpp"

namespace zygarde::scripting::types {
/// @brief Fixed Update callback function
using FixedUpdateFunction = std::function<void(ScriptingContext::ConstPtr)>;
/// @brief Colliding callback function
using Collision2DFunction =
    std::function<void(ScriptingContext::ConstPtr, physics::types::Collision2D::ptr)>;
}  // namespace zygarde::scripting::types
