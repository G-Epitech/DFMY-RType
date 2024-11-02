/*
** EPITECH PROJECT, 2024
** database.hpp
** File description:
** Database class
*/

#pragma once

#include "abra/includes/database.hpp"
#include "libs/game/src/api/server/database/props/scores.hpp"
#include "libs/game/src/core.hpp"

namespace rtype::sdk::game::api {
class EXPORT_GAME_SDK_API Database;
}

class rtype::sdk::game::api::Database {
 public:
  /**
   * @brief Construct a new Database object
   * @param props The connection properties
   */
  explicit Database(const abra::database::MySQL::ConnectionProps &props);

  /**
   * @brief Insert a score into the database
   * @param score The score to insert
   */
  void InsertScore(const schema::Score &score);

  /**
   * @brief Get the best scores
   * @param max The maximum number of scores to get
   * @return std::vector<schema::Score> The best scores
   */
  std::vector<schema::Score> GetBestScores(unsigned int max);

 private:
  /// @brief The MySQL database
  abra::database::MySQL db_;
};
