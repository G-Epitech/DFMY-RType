/*
** EPITECH PROJECT, 2024
** logger.cpp
** File description:
** Logger class
*/

#include "logger.hpp"

#include <iostream>
#include <utility>

using namespace abra::tools;

Logger::Logger(std::string name) : name_(std::move(name)) {}

Logger::~Logger() = default;

void Logger::Info(const std::string &message, const std::string emoji) const {
  std::cout << emoji << "\\e[0;30m " << name_ << ": " << message << "\\e[0m" << std::endl;
}

void Logger::Warning(const std::string &message, const std::string emoji) const {
  std::cout << emoji << " \\e[4;33mWARNING\\e[1;33m " << name_ << ": " << message << "\\e[0m"
            << std::endl;
}

void Logger::Error(const std::string &message, const std::string emoji) const {
  std::cerr << emoji << " \\e[1;31mERROR\\e[1;31m " << name_ << ": " << message << "\\e[0m"
            << std::endl;
}
