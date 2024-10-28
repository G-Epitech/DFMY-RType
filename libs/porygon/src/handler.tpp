/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** provider.tpp
*/

#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <utility>

namespace porygon {

template <typename T, typename... Args>
T DependenciesHandler::MakeWithDependencies(Args&&... args) {
  if constexpr (ConstructibleWithDependenciesHandlerPtr<T, Args...>) {
    return T(GetShared(), std::forward<Args>(args)...);
  } else {
    return T(std::forward<Args>(args)...);
  }
}

template <typename T, typename... Args>
std::shared_ptr<T> DependenciesHandler::MakeSharedWithDependencies(Args&&... args) {
  if constexpr (ConstructibleWithDependenciesHandlerPtr<T, Args...>) {
    return std::make_shared<T>(GetShared(), std::forward<Args>(args)...);
  } else {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }
}

template <typename T, typename... Args>
DependenciesHandler& DependenciesHandler::Add(Args&&... args) {
  builders_[std::type_index(typeid(T))] =
      [this, ... args = std::decay_t<Args>(std::forward<Args>(args))]() mutable {
        return MakeSharedWithDependencies<T>(std::forward<decltype(args)>(args)...);
      };
  return *this;
}

template <typename T>
DependenciesHandler& DependenciesHandler::AddInstance(std::shared_ptr<T> instance) {
  instances_[std::type_index(typeid(T))] = std::move(instance);
  return *this;
}

template <typename T>
std::shared_ptr<T> DependenciesHandler::Get() {
  auto instance = GetInstance<T>();

  if (!instance) {
    instance = BuildInstance<T>();
  }
  return instance;
}

template <typename T>
std::shared_ptr<T> DependenciesHandler::GetOrThrow() {
  auto instance = Get<T>();

  if (!instance) {
    throw std::runtime_error("Instance of " + utils::GetTypeName<T>() + " not found.");
  }
  return instance;
}

template <typename T>
bool DependenciesHandler::Has() const {
  auto in_instance = instances_.find(std::type_index(typeid(T))) != instances_.end();
  auto in_builder = builders_.find(std::type_index(typeid(T))) != builders_.end();

  return in_instance || in_builder;
}

template <typename T>
std::shared_ptr<T> DependenciesHandler::GetInstance() {
  auto it = instances_.find(std::type_index(typeid(T)));
  if (it != instances_.end()) {
    return std::static_pointer_cast<T>(it->second);
  }
  return nullptr;
}

template <typename T>
std::shared_ptr<T> DependenciesHandler::BuildInstance() {
  auto it = builders_.find(std::type_index(typeid(T)));
  if (it == builders_.end()) {
    std::cout << "[WARN]: Manager " << utils::GetTypeName<T>() << " not registered." << std::endl;
    return nullptr;
  }
  auto& builder = it->second;
  auto& instance = instances_[std::type_index(typeid(T))] = builder();

  builders_.erase(it);
  return std::static_pointer_cast<T>(instance);
}
}  // namespace porygon
