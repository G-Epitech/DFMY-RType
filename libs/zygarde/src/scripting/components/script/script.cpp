/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Script.cpp
*/

#include "script.hpp"

#include <utility>

using namespace zygarde::scripting::components;

Script::Script(scripting::types::Collision2DFunction on_collision_enter,
               scripting::types::FixedUpdateFunction fixed_update,
               scripting::types::ValuesMap values)
    : onCollisionEnter(std::move(on_collision_enter)),
      fixedUpdate(std::move(fixed_update)),
      values_(std::move(values)) {}

Script::Script(scripting::types::Collision2DFunction on_collision_enter,
               scripting::types::FixedUpdateFunction fixed_update)
    : onCollisionEnter(std::move(on_collision_enter)), fixedUpdate(std::move(fixed_update)) {}
