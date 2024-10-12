/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** settings.hpp
*/

#pragma once

#include "bases/scene_base.hpp"
#include "context/global_context.hpp"
#include "core/types/vector/vector.hpp"

namespace rtype::client {
class SceneSettings final : public SceneBase<GlobalContext> {
 public:
  explicit SceneSettings(const GlobalContext &context);

  ~SceneSettings() override = default;

  void Update(utils::DeltaTime delta_time) override;

  void OnCreate() override;

  void OnActivate() override;

 private:
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
   * @param position The position of the radio options.
   */
  void CreateColorBlindnessRadioOption(const std::string &label, const std::string &value,
                                       const zygarde::core::types::Vector2f &position);

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

  void CreateDisableAnimationsButton(const float &x, const float &y) const;
  void CreateDisableAnimationsLabel(const float &x, const float &y) const;
};
}  // namespace rtype::client
