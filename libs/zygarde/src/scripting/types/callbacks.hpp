/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** callbacks.hpp
*/

#pragma once
/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** functions.hpp
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
using FixedUpdateFunction = std::function<void(const ScriptingContext &)>;
/// @brief Colliding callback function
using Collision2DFunction =
    std::function<void(const ScriptingContext &, physics::components::Collision2D::Ptr)>;
}  // namespace zygarde::scripting::types
