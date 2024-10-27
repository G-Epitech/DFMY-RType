/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** mono_behaviour.hpp
*/

#pragma once

#include <functional>

#include "scripting/components/mono_behaviour/mono_behaviour.hpp"

namespace zygarde::scripting::types {
using MonoBehaviourCreater = std::function<scripting::components::MonoBehaviour::Instance()>;
using ScriptsMap = std::unordered_map<std::string, MonoBehaviourCreater>;
}  // namespace zygarde::scripting::types
