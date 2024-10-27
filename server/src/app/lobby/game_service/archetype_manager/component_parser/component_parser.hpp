/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ComponentParser.hpp
*/

#pragma once

#include <nlohmann/json.hpp>

#include "zygarde/includes/components.hpp"
#include "zygarde/src/scripting/types/context.hpp"

namespace rtype::server::tools {
class ComponentParser {
 public:
  ComponentParser() = delete;
  ~ComponentParser() = default;

  static zygarde::physics::components::Rigidbody2D ParseRigidbody2D(const nlohmann::json &json);
  static zygarde::physics::components::BoxCollider2D ParseBoxCollider2D(const nlohmann::json &json);
  static zygarde::core::components::Position ParsePosition(const nlohmann::json &json);
  static zygarde::core::components::Tags ParseTags(const nlohmann::json &json);
  static std::unordered_map<std::string, zygarde::scripting::types::ValuesMap> ParseScriptPoolData(
      const nlohmann::json &json);

 private:
  static std::pair<std::string, zygarde::scripting::types::ValuesMap> ParseScriptData(
      const nlohmann::json &json);
  static scripting::types::ValuesMap ParseCustomScriptValues(const nlohmann::json &json);
};
}  // namespace rtype::server::tools
