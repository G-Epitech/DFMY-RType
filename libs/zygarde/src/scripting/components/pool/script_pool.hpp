/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ScriptPool.hpp
*/

#pragma once

#include <list>
#include <memory>
#include <vector>

#include "api.hpp"
#include "scripting/components/mono_behaviour/mono_behaviour.hpp"

namespace zygarde::scripting::components {
class EXPORT_ZYGARDE_API ScriptPool final {
 public:
  ScriptPool() = default;
  ~ScriptPool() = default;

  /**
   * @brief Construct a new Script Pool object
   * @param scripts Scripts to add to the pool
   */
  explicit ScriptPool(std::list<std::shared_ptr<MonoBehaviour>> scripts);

  /**
   * @brief Construct a new Script Pool object
   * @param script Script to add to the pool
   */
  explicit ScriptPool(std::shared_ptr<MonoBehaviour> script);

  ScriptPool(const ScriptPool&) = default;             // Copy constructor
  ScriptPool(ScriptPool&&) noexcept = default;         // Move constructor
  ScriptPool& operator=(const ScriptPool&) = default;  // Copy assignment
  ScriptPool& operator=(ScriptPool&&) noexcept = default;

 public:
  /**
   * @brief Add a script to the pool
   * @param script Script to add
   */
  void AddScript(const std::shared_ptr<MonoBehaviour>& script);

  /**
   * @brief Get a script from the pool
   * @tparam T Script type
   * @return Script shared pointer
   */
  template <typename T>
  [[nodiscard]] std::shared_ptr<T> GetScript();

  /**
   * @brief Get all scripts from the pool
   * @return Vector of scripts
   */
  [[nodiscard]] inline std::list<std::shared_ptr<MonoBehaviour>> GetScripts() noexcept {
    return scripts_;
  }

 private:
  /// @brief Vector of scripts
  std::list<std::shared_ptr<MonoBehaviour>> scripts_ = {};
};
}  // namespace zygarde::scripting::components

#include "script_pool.tpp"
