/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ScriptPool.cpp
*/

#include "script_pool.hpp"

using namespace zygarde::scripting::components;

void ScriptPool::AddScript(const std::shared_ptr<MonoBehaviour>& script) {
  scripts_.push_back(script);
}
ScriptPool::ScriptPool(std::vector<std::shared_ptr<MonoBehaviour>> scripts)
    : scripts_(std::move(scripts)) {}
