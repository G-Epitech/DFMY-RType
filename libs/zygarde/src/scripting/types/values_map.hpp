/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** values_map.hpp
*/

#pragma once

#include <any>
#include <map>
#include <string>

namespace zygarde::scripting::types {
/// @brief Map of values mainly used for custom script values
using ValuesMap = std::map<std::string, std::any>;
}  // namespace zygarde::scripting::types
