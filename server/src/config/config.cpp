/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** config.cpp
*/

#include "config.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

using namespace rtype::server;

Config::Config(const std::string& configPath) {
  Load(configPath);
}

void Config::Load(const std::string& configPath) {
  if (!std::filesystem::exists(configPath)) {
    throw std::runtime_error("Config file not found\n");
  }
  std::ifstream file(configPath);

  return ParseFile(file);
}

void Config::ParseFile(std::ifstream& file) {
  std::string line;
  std::size_t pos;

  while (std::getline(file, line)) {
    pos = line.find('=');
    if (pos == std::string::npos) {
      continue;
    }
    std::string key = line.substr(0, pos);
    std::string value = line.substr(pos + 1);
    mConfig[key] = ParseValueType(value);
  }
}

std::any Config::ParseValueType(const std::string& configValue) {
  if (configValue == "true" || configValue == "false") {
    return configValue == "true";
  }

  char* end;
  int intValue = std::strtol(configValue.c_str(), &end, 10);
  if (*end == '\0') {
    return intValue;
  }

  double floatValue = std::strtod(configValue.c_str(), &end);
  if (*end == '\0') {
    return floatValue;
  }
  return {configValue};
}
