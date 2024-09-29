/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** env.cpp
*/

#include "env.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

using namespace rtype::server;

Env::Env(const std::string& envPath) {
  Load(envPath);
}

Env::EnvMap Env::Load(const std::string& envPath) {
  if (!std::filesystem::exists(envPath)) {
    throw std::runtime_error("Env file not found\n");
  }
  std::ifstream file(envPath);

  return ParseFile(file);
}

Env::EnvMap Env::ParseFile(std::ifstream& file) {
  std::string line;
  std::size_t pos;

  while (std::getline(file, line)) {
    pos = line.find('=');
    if (pos == std::string::npos) {
      continue;
    }
    std::string key = line.substr(0, pos);
    std::string value = line.substr(pos + 1);
    mEnv[key] = ParseValueType(value);
  }
  return mEnv;
}

std::any Env::ParseValueType(const std::string& envValue) {
  if (envValue == "true" || envValue == "false") {
    return envValue == "true";
  }

  char* end;
  int intValue = std::strtol(envValue.c_str(), &end, 10);
  if (*end == '\0') {
    return intValue;
  }

  double floatValue = std::strtod(envValue.c_str(), &end);
  if (*end == '\0') {
    return floatValue;
  }
  return {envValue};
}
