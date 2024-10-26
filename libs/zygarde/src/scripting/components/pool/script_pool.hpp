/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ScriptPool.hpp
*/

#pragma once

#include <memory>
#include <vector>

#include "api.hpp"
#include "scripting/components/mono_behaviour/mono_behaviour.hpp"

namespace zygarde::scripting::components {
class EXPORT_ZYGARDE_API ScriptPool final {
 public:
  ScriptPool() = default;
  ~ScriptPool() = default;

  explicit ScriptPool(std::vector<std::shared_ptr<MonoBehaviour>> scripts);

  explicit ScriptPool(std::shared_ptr<MonoBehaviour> script);

 public:
  void AddScript(const std::shared_ptr<MonoBehaviour>& script);

  template <typename T>
  [[nodiscard]] std::shared_ptr<T> GetScript();

  [[nodiscard]] inline std::vector<std::shared_ptr<MonoBehaviour>> GetScripts() noexcept {
    return scripts_;
  }

 private:
  std::vector<std::shared_ptr<MonoBehaviour>> scripts_;
};
}  // namespace zygarde::scripting::components

#include "script_pool.tpp"
