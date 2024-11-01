/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** mono_behaviour.hpp
*/

#pragma once

#include <functional>
#include <map>

namespace zygarde::scripting::components {
class MonoBehaviour;
}

namespace zygarde::scripting::types {
/// @brief Function to create a MonoBehaviour
using MonoBehaviourCreater = std::function<std::shared_ptr<scripting::components::MonoBehaviour>()>;
/// @brief Map of scripts creator callbacks
using ScriptsMap = std::map<std::string, MonoBehaviourCreater>;
}  // namespace zygarde::scripting::types
