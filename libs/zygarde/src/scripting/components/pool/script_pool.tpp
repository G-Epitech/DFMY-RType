/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** script.tpp
*/

#pragma once

template <typename T>
std::shared_ptr<T> zygarde::scripting::components::ScriptPool::GetScript() {
  for (const auto& script : scripts_) {
    if (auto scriptInstance = std::dynamic_pointer_cast<T>(script)) {
      return scriptInstance;
    }
  }
  return nullptr;
}
