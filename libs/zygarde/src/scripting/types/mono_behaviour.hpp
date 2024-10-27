/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** mono_behaviour.hpp
*/

#pragma once

#include <functional>

namespace zygarde::scripting::components {
class MonoBehaviour;
}

namespace zygarde::scripting::types {
using MonoBehaviourCreater = std::function<std::shared_ptr<scripting::components::MonoBehaviour>()>;
using ScriptsMap = std::unordered_map<std::string, MonoBehaviourCreater>;
}  // namespace zygarde::scripting::types
