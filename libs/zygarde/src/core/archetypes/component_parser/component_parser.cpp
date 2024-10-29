/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ComponentParser.cpp
*/

#include "component_parser.hpp"

using namespace zygarde::core::archetypes;

zygarde::physics::components::Rigidbody2D ComponentParser::ParseRigidbody2D(
    const nlohmann::json& json) {
  zygarde::physics::components::Rigidbody2D rigidbody2d;

  if (!json.contains("data")) {
    return rigidbody2d;
  }
  const auto& data = json["data"];
  !data.contains("isKinematic") ? rigidbody2d.SetKinematic(false)
                                : rigidbody2d.SetKinematic(data["isKinematic"].get<bool>());
  if (!data.contains("velocity")) {
    rigidbody2d.SetVelocity({0, 0});
  } else {
    rigidbody2d.SetVelocity({data["velocity"]["x"], data["velocity"]["y"]});
  }
  !data.contains("drag") ? rigidbody2d.SetDrag(1) : rigidbody2d.SetDrag(data["drag"].get<float>());
  return rigidbody2d;
}

zygarde::physics::components::BoxCollider2D ComponentParser::ParseBoxCollider2D(
    const nlohmann::json& json) {
  zygarde::core::types::Vector2f size;
  std::vector<int> includeLayers = {};
  std::vector<int> collisionLayers = {};

  if (!json.contains("data")) {
    return {size, collisionLayers, includeLayers};
  }
  const auto& data = json["data"];
  !data.contains("size") ? size = {0, 0} : size = {data["size"]["x"], data["size"]["y"]};

  !data.contains("includeLayers") ? includeLayers = {}
                                  : includeLayers = data["includeLayers"].get<std::vector<int>>();

  !data.contains("collisionLayers")
      ? collisionLayers = {}
      : collisionLayers = data["collisionLayers"].get<std::vector<int>>();

  return {size, collisionLayers, includeLayers};
}

zygarde::core::components::Position ComponentParser::ParsePosition(const nlohmann::json& json) {
  zygarde::core::components::Position position;

  if (!json.contains("data") || !json["data"].contains("point")) {
    position.point = zygarde::core::types::Vector3f{0, 0, 0};
  } else {
    const auto& data = json["data"];
    position.point = zygarde::core::types::Vector3f{data["point"]["x"].get<float>(),
                                                    data["point"]["y"].get<float>(),
                                                    data["point"]["z"].get<float>()};
  }
  return position;
}

zygarde::core::components::Tags ComponentParser::ParseTags(const nlohmann::json& json) {
  std::set<std::string> tags;

  if (!json.contains("data") || !json["data"].contains("tags")) {
    tags = {};
  } else {
    const auto& data = json["data"];
    tags = data["tags"].get<std::set<std::string>>();
  }
  return zygarde::core::components::Tags{tags};
}

std::unordered_map<std::string, zygarde::scripting::types::ValuesMap>
ComponentParser::ParseScriptPoolData(const nlohmann::json& json) {
  std::unordered_map<std::string, zygarde::scripting::types::ValuesMap> scripts;

  if (!json.contains("data")) {
    return scripts;
  }
  const auto& data = json["data"];
  for (auto& scriptJSON : data) {
    const auto [scriptName, valuesMap] = ParseScriptData(scriptJSON);
    scripts[scriptName] = valuesMap;
  }
  return scripts;
}

std::pair<std::string, zygarde::scripting::types::ValuesMap> ComponentParser::ParseScriptData(
    const nlohmann::json& json) {
  zygarde::scripting::types::ValuesMap values;
  std::string scriptName;

  scriptName = json["scriptName"].get<std::string>();
  if (!json.contains("customValues")) {
    return {scriptName, values};
  }
  values = ParseCustomScriptValues(json["customValues"]);
  return {scriptName, values};
}

scripting::types::ValuesMap ComponentParser::ParseCustomScriptValues(const nlohmann::json& json) {
  scripting::types::ValuesMap values;

  for (auto& [key, value] : json.items()) {
    if (value.is_string()) {
      values[key] = value.get<std::string>();
    } else if (value.is_number_float()) {
      values[key] = value.get<float>();
    } else if (value.is_number_integer()) {
      values[key] = value.get<int>();
    } else if (value.is_boolean()) {
      values[key] = value.get<bool>();
    }
  }
  return values;
}
