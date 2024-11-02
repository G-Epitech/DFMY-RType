/*
** EPITECH PROJECT, 2024
** database.cpp
** File description:
** Database class
*/

#include "database.hpp"

using namespace rtype::sdk::game::api;

Database::Database(const abra::database::MySQL::ConnectionProps &props)
    : db_(props), logger_("Database") {
  logger_.Info("Database connected", "💽");
}

void Database::InsertScore(const schema::Score &score) {
  std::string query = "INSERT INTO scores (room_name, score, win) VALUES ('" + score.roomName +
                      "', " + std::to_string(score.score) + ", " + std::to_string(score.win) + ");";

  db_.Execute(query);
}

std::vector<schema::Score> Database::GetBestScores(unsigned int max) {
  std::string query = "SELECT * FROM scores ORDER BY score DESC LIMIT " + std::to_string(max) + ";";
  auto results = db_.Execute(query);
  std::vector<schema::Score> scores;

  auto rows = results.rows();

  for (const auto &row : rows) {
    schema::Score score;
    score.id = row[0].as_int64();
    score.roomName = row[1].as_string();
    score.score = row[2].as_int64();
    score.win = row[3].as_int64();
    scores.push_back(score);
  }
  return scores;
}
