/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** config.hpp
*/

#pragma once

#include <any>
#include <string>
#include <unordered_map>

namespace rtype::server {
class Env {
  typedef std::unordered_map<std::string, std::any> EnvMap;

 public:
  Env() = default;
  ~Env() = default;

  EnvMap Load(const std::string& configPath);

  template <class T>
  T Get(const std::string &key);

 private:
  EnvMap ParseFile(std::ifstream& file);

  static std::any ParseValueType(const std::string& envValue);

 private:
  EnvMap mEnv;
};

}  // namespace rtype::server::cli

#include "env.tpp"
