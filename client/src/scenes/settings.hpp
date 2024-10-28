/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** settings.hpp
*/

#pragma once

#include "libs/mew/src/scenes/scene_base.hpp"
#include "libs/zygarde/src/core/components/components.hpp"
#include "libs/zygarde/src/core/types/vector/vector.hpp"

namespace rtype::client::scenes {

using namespace mew::scenes;

class SceneSettings final : public SceneBase {
 public:
  /**
   * @brief Construct a new Scene Settings object
   * @param services Services provider
   */
  explicit SceneSettings(DependenciesHandler::Ptr services);

  ~SceneSettings() override = default;

  void Update(DeltaTime delta_time) override;

  void OnCreate() override;

  void OnActivate() override;

 private:
  /// @brief Store the settings manager
  mew::managers::SettingsManager::Ptr settingsManager_;

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
   * @brief Create the fullscreen button
   * @param x The x position of the button (Vertical axis).
   * @param y The y position of the button (Horizontal axis).
   */
  void CreateFullscreenButton(const float &x, const float &y) const;

  /**
   * @brief Create the fullscreen label
   * @param x The x position of the label (Vertical axis).
   * @param y The y position of the label (Horizontal axis).
   */
  void CreateFullscreenLabel(const float &x, const float &y) const;

  /**
   * @brief Create the volume label
   * @param x The x position of the label (Vertical axis).
   * @param y The y position of the label (Horizontal axis).
   */
  void CreateDisableSoundsButton(const float &x, const float &y) const;

  /**
   * @brief Create the volume label
   * @param x The x position of the label (Vertical axis).
   * @param y The y position of the label (Horizontal axis).
   */
  void CreateDisableSoundsLabel(const float &x, const float &y) const;

  /**
   * @brief Create the volume label
   * @param x The x position of the label (Vertical axis).
   * @param y The y position of the label (Horizontal axis).
   */
  void CreateDisableMusicButton(const float &x, const float &y) const;

  /**
   * @brief Create the volume label
   * @param x The x position of the label (Vertical axis).
   * @param y The y position of the label (Horizontal axis).
   */
  void CreateDisableMusicLabel(const float &x, const float &y) const;

  /**
   * @brief Create the color blindness label and radio options
   * @param label The label of the radio options.
   * @param value The value of the radio options.
   * @param pos The position of the radio options.
   */
  void CreateColorBlindnessRadioOption(const std::string &label, const std::string &value,
                                       const zygarde::core::types::Vector2f &pos);

  /**
   * @brief Create the color blindness label
   * @param x The x position of the label (Vertical axis).
   * @param y The y position of the label (Horizontal axis).
   */
  void CreateColorBlindnessLabel(const float &x, const float &y) const;

  /**
   * @brief Create the color blindness setting
   * @param x The x position of the setting (Vertical axis).
   * @param y The y position of the setting (Horizontal axis).
   *
   */
  void CreateColorBlindnessSetting(const float &x, const float &y);

  /**
   * @brief Unselect all radio option except the selected one
   * @param selected_value Selected value of the radio options.
   */
  void SelectColorBlindnessRadioOptions(const std::string &selected_value);

  /**
   * @brief Create the volume label
   * @param x Position of the label on the x axis
   * @param y Position of the label on the y axis
   */
  void CreateDisableAnimationsButton(const float &x, const float &y) const;

  /**
   * @brief Create the volume label
   * @param x Position of the label on the x axis
   * @param y Position of the label on the y axis
   */
  void CreateDisableAnimationsLabel(const float &x, const float &y) const;

  /**
   * @brief Create the keymap label
   * @param x Position of the label on the x axis
   * @param y Position of the label on the y axis
   */
  void CreateKeyMapLabel(const float &x, const float &y) const;

  /**
   * @brief Create a new radio option for the keymap
   * @param label The label of the radio options.
   * @param value The value of the radio options.
   * @param position The position of the radio options.
   */
  void CreateKeyMapRadioOption(const std::string &label, const std::string &value,
                               const zygarde::core::types::Vector2f &position);

  void SelectKeyMapRadioOptions(const std::string &selected_value);

  /**
   * @brief Create the keymap setting
   * @param x Position of the setting on the x axis
   * @param y Y position of the setting on the y axis
   */
  void CreateKeyMapSetting(const float &x, const float &y);
};
}  // namespace rtype::client::scenes
