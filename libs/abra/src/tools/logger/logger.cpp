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

void Logger::Info(const std::string &message, const std::string &emoji) const {
  if (!emoji.empty()) {
    std::cout << emoji << " ";
  }
  std::cout << "\033[0;30m" << name_ << ": " << message << "\033[0m" << std::endl;
}

void Logger::Warning(const std::string &message, const std::string &emoji) const {
  if (!emoji.empty()) {
    std::cout << emoji << " ";
  }
  std::cout << "\033[1;33mWARNING\033[0;33m " << name_ << ": " << message << "\033[0m" << std::endl;
}

void Logger::Error(const std::string &message, const std::string &emoji) const {
  if (!emoji.empty()) {
    std::cout << emoji << " ";
  }
  std::cerr << "\033[1;31mERROR\033[0;31m " << name_ << ": " << message << "\033[0m" << std::endl;
}
