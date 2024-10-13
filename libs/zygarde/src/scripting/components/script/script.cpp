/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Script.cpp
*/

#include "script.hpp"

#include <utility>

using namespace zygarde::scripting::components;

Script::Script(std::optional<types::Collision2DFunction> on_collision_enter,
               std::optional<types::FixedUpdateFunction> fixed_update,
               const scripting::types::ValuesMap& values)
    : onCollisionEnter(std::move(on_collision_enter)),
      fixedUpdate(std::move(fixed_update)),
      values_(std::make_shared<types::ValuesMap>(values)) {}

Script::Script(std::optional<scripting::types::Collision2DFunction> on_collision_enter,
               std::optional<scripting::types::FixedUpdateFunction> fixed_update)
    : onCollisionEnter(std::move(on_collision_enter)), fixedUpdate(std::move(fixed_update)) {}
