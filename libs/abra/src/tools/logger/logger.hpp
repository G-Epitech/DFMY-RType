/*
** EPITECH PROJECT, 2024
** logger.hpp
** File description:
** Logger class
*/

#pragma once

#include <string>

#include "libs/abra/src/core.hpp"

namespace abra::tools {
class EXPORT_NETWORK_SDK_API Logger;
}

class abra::tools::Logger {
 public:
  /**
   * @brief Construct a new Logger interface
   * @param name The name of the logger service
   */
  explicit Logger(std::string name);

  ~Logger();

  /**
   * @brief Log an information message
   * @param message The message to log
   * @param emoji The emoji to display (default: none)
   */
  void Info(const std::string& message, const std::string& emoji = "") const;

  /**
   * @brief Log an warning message
   * @param message The message to log
   * @param emoji The emoji to display (default: none)
   */
  void Warning(const std::string& message, const std::string& emoji = "") const;

  /**
   * @brief Log an error message
   * @param message The message to log
   * @param emoji The emoji to display (default: none)
   */
  void Error(const std::string& message, const std::string& emoji = "") const;

 private:
  const std::string name_;
};
