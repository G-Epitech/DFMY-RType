/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** tag.hpp
*/

#pragma once

#include <set>
#include <string>

#include "libs/zygarde/src/api.hpp"

namespace zygarde::core::components {
class EXPORT_ZYGARDE_API Tags final {
 public:
  /**
   * @brief Build a tags with a set of tags
   * @param tags Tags to add
   */
  explicit Tags(const std::set<std::string> &tags);

  /**
   * @brief Default constructor
   */
  Tags() = default;

  /**
   * @brief Destructor
   */
  ~Tags() = default;

  /**
   * @brief Check if the tag contains a specific tag
   * @param tag Tag to check
   * @return Match result
   */
  bool operator&(const std::string &tag) const;

  bool operator==(const std::string &tag) const;

  /**
   * @brief Add a tag to the tag
   * @param tag Tag to add
   */
  void AddTag(const std::string &tag);

  /**
   * @brief Remove a tag from the tag
   * @param tag Tag to remove
   */
  void RemoveTag(const std::string &tag);

 private:
  std::set<std::string> tags_{};
};
}  // namespace zygarde::core::components
