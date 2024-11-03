/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** start.hpp
*/

#pragma once

#include "client/src/services/rooms_service.hpp"
#include "client/src/ui/select/select.hpp"
#include "libs/mew/src/scenes/scene_base.hpp"

namespace rtype::client::scenes {

using namespace mew::scenes;

class SceneStart final : public SceneBase {
 public:
  /**
   * @brief Construct a new Start Scene object
   * @param services Services to be injected
   */
  explicit SceneStart(DependenciesHandler::Ptr services);

  /**
   * @brief Destroy the Start Scene object
   */
  ~SceneStart() final = default;

 private:
  void OnCreate() override;

  void Update(DeltaTime delta_time) override;

  /**
   * @brief Update select of nodes and rooms
   */
  void UpdateSelects();

  /**
   * @brief Update the controls
   * @param room_id Room id to be updated
   */
  void UpdateControls(const std::optional<std::string> &room_id);

  /**
   * @brief Create main entity
   */
  void CreateMainEntity();

  /**
   * @brief Add the static labels
   */
  void CreateStaticLabels();

  /**
   * @brief Create the select fields
   * @param rooms Rooms to be injected
   */
  inline ui::Select::Properties GetNodeSelectProps(const services::RoomsService::RoomsMap &rooms);

  /**
   * @brief Create the select fields
   * @param rooms Rooms to be injected
   * @param node_id Current node selected
   */
  inline ui::Select::Properties GetRoomsSelectProps(
      const services::RoomsService::RoomsMap &rooms,
      std::optional<services::RoomsService::NodeIdType> node_id);

  /**
   * @brief Create the select fields
   */
  void CreateNodeSelectLabel();

  /**
   * @brief Create the select fields
   */
  void CreateRoomSelectLabel();

  /**
   * @brief Create the select fields
   */
  void CreateSelects();

  /**
   * @brief Create the controls
   */
  void CreateControls();

  /**
   * @brief Back button
   */
  void CreateBackButton();

  /**
   * @brief Update the selected node id
   */
  void UpdateSelectedNode();

  /**
   * @brief Create the room info rectangle with its label
   */
  void CreateRoomInfoArea();

  /**
   * @brief Update room infos
   * @param room_id Room id to be updated
   */
  void UpdateRoomInfos(const std::optional<std::string> &room_id);

  /**
   * @brief Make room visible
   * @param room Room to display
   */
  void SetRoomInfo(const services::RoomsService::RoomStatusType &room);

  /**
   * @brief Hide room info
   */
  void HideRoomInfo();

  /**
   * @brief Update room infos
   */
  void CreateRoomInfosContent();

  /**
   * @brief Try to join the room
   */
  void OnJoinRoom();

  /// @brief Server connection service
  services::RoomsService::Ptr roomsService_;

  /// @brief Last refresh time
  std::chrono::system_clock::time_point lastRefreshTime_;

  /// @Selected node
  std::optional<services::RoomsService::NodeIdType> selectedNode_;
};
}  // namespace rtype::client::scenes
