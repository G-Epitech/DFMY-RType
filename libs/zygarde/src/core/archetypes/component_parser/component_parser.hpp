/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ComponentParser.hpp
*/

#pragma once

#include <nlohmann/json.hpp>

#include "api.hpp"
#include "libs/zygarde/includes/components.hpp"
#include "scripting/types/scripting_context.hpp"

namespace zygarde::core::archetypes {
class EXPORT_ZYGARDE_API ComponentParser final {
 public:
  ComponentParser() = delete;
  ~ComponentParser() = default;

  /**
   * @brief Parse a Rigidbody2D component from a json object
   * @param json Json object to parse
   * @return Rigidbody2D component
   */
  static zygarde::physics::components::Rigidbody2D ParseRigidbody2D(const nlohmann::json &json);

  /**
   * @brief Parse a BoxCollider2D component from a json object
   * @param json Json object to parse
   * @return BoxCollider2D component
   */
  static zygarde::physics::components::BoxCollider2D ParseBoxCollider2D(const nlohmann::json &json);

  /**
   * @brief Parse a Position component from a json object
   * @param json Json object to parse
   * @return Position component
   */
  static zygarde::core::components::Position ParsePosition(const nlohmann::json &json);

  /**
   * @brief Parse a Tags component from a json object
   * @param json Json object to parse
   * @return Tags component
   */
  static zygarde::core::components::Tags ParseTags(const nlohmann::json &json);

  /**
   * @brief Parse a ScriptPool data from a json object
   * @param json Json object to parse
   * @return ScriptPool data (script name, custom values to provide the script)
   * @see zygarde::scripting::types::ValuesMap
   * @see zygarde::scripting::components::ScriptPool OnEnable method
   */
  static std::unordered_map<std::string, zygarde::scripting::types::ValuesMap> ParseScriptPoolData(
      const nlohmann::json &json);

 private:
  /**
   * @brief Parse a single script data from a json object
   * @param json Json object to parse
   * @return Script data (script name, custom values to provide the script)
   */
  static std::pair<std::string, zygarde::scripting::types::ValuesMap> ParseScriptData(
      const nlohmann::json &json);

  /**
   * @brief Parse custom script values from a json object
   * @param json Json object to parse
   * @return Custom script values
   * @see zygarde::scripting::types::ValuesMap
   * @see zygarde::scripting::components::ScriptPool OnEnable method
   */
  static scripting::types::ValuesMap ParseCustomScriptValues(const nlohmann::json &json);
};
}  // namespace zygarde::core::archetypes
