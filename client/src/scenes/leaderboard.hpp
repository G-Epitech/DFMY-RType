/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** leaderboard.hpp
*/

#pragma once

#include "client/src/services/server_connection_service.hpp"
#include "libs/mew/src/scenes/scene_base.hpp"
#include "libs/zygarde/src/core/components/components.hpp"

namespace rtype::client::scenes {

using namespace mew::scenes;

class SceneLeaderboard final : public SceneBase {
 public:
  /**
   * @brief Construct a new Scene Leaderboard object
   * @param services Services provider
   */
  explicit SceneLeaderboard(DependenciesHandler::Ptr services);

  ~SceneLeaderboard() override = default;

  void Update(DeltaTime delta_time) override;

  void OnCreate() override;

  void OnActivate() override;

 private:
  /// @brief Server connection service
  services::ServerConnectionService::Ptr serverConnectionService_;

  /**
   * @brief Create main entity
   */
  void CreateMainEntity() const;

  /**
   * @brief Create the title
   */
  void CreateTitle() const;

  /**
   * @brief Create the back button
   */
  void CreateBackButton() const;

  /**
   * @brief Create the leaderboard
   */
  void CreateLeaderboard() const;

  /**
   * @brief Create a leaderboard entry
   * @param name Name of the player
   * @param score Score of the player
   * @param win Did the players win
   * @param index Index of the entry
   */
  void CreateLeaderboardEntry(const std::string &name, const std::string &score, const bool &win,
                              const std::size_t &index) const;

  /**
   * @brief Create the score rectangle
   * @param index Index of the entry
   * @param size Size of the rectangle
   * @param origin Origin of the rectangle
   */
  void CreateScoreRectangle(const std::size_t &index, const sf::Vector2f &size, const zygarde::core::types::Vector3f &origin) const;

  /**
   * @brief Create the score title
   * @param name Name of the title
   * @param origin Origin of the title
   */
  void CreateScoreTitle(const std::string &name, const zygarde::core::types::Vector3f &origin) const;


  /**
   * @brief Create the score info
   * @param score Score
   * @param origin Origin of the info
   */
  void CreateScoreInfo(const std::string &score, const zygarde::core::types::Vector3f &origin) const;

  /**
   * @brief Create the score win
   * @param win Did the player win
   * @param origin Origin of the win
   */
  void CreateScoreWin(const bool &win, const zygarde::core::types::Vector3f &origin) const;
};
}  // namespace rtype::client::scenes
