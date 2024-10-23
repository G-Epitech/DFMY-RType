/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** window_manager.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include <optional>

#include "manager_base.hpp"

namespace mew::managers {
class WindowManager : public ManagerBase {
 public:
  /// @brief Deferred events
  typedef std::vector<sf::Event> EventsDeferrer;

  /// @brief Pointer to a window manager
  typedef std::shared_ptr<WindowManager> Ptr;

  struct Properties {
    std::string title;                    ///< Title of the window
    sf::VideoMode videoMode;              ///< Video mode of the window
    sf::Uint32 style;                     ///< Style of the window
    sf::ContextSettings contextSettings;  ///< Context settings of the window
    sf::Uint32 frameLimit;                ///< Frame limit of the window
    std::optional<std::string> iconPath;  ///< Path to the icon of the window
  };

  /// @brief Views of the window
  enum View {
    GAME,  ///< Game view
    HUD,   ///< HUD view
  };

  /**
   * @brief Construct a new Window Manager object
   * @param services Managers provider
   * @param props Properties of the window
   */
  WindowManager(DependenciesHandler::Ptr services, const Properties &props);

  /**
   * @brief Construct a new Window Manager object
   */
  ~WindowManager() = default;

  /**
   * @brief Get the Window object
   */
  std::shared_ptr<sf::RenderWindow> window() { return window_; }

  /**
   * @brief Defer events
   */
  void DeferEvents();

  /**
   * @brief Clear deferred events
   */
  void ClearEvents() noexcept;

  /**
   * @brief Check if the window is active
   * @return Active status of the window
   */
  bool IsActive() const;

  /**
   * @brief Get deferred events
   * @return Events list that have been deferred
   */
  const EventsDeferrer &GetDeferredEvents();

  /**
   * @brief Set the window view to the game view
   */
  void SetView(const View &view) const;

  /**
   * @brief Get the style of the window
   * @return Style of the window
   */
  sf::Uint32 GetStyle() const;

  /**
   * @brief Set the style of the window
   * @param style Style of the window
   */
  void SetStyle(const sf::Uint32 &style);

  /**
   * @brief Set the shader of the window
   * @param name Name of the shader
   */
  void SetShader(const std::string &name);

  /**
   * @brief Get the selected shader
   * @return Selected shader
   */
  std::shared_ptr<sf::Shader> GetSelectedShader() const;

  /// @brief Get the width of the window
  float width_;
  /// @brief Get the height of the window
  float height_;

 private:
  /// @brief Average length of the events list
  static constexpr const int kEventsAverageLength = 5;

  /// @brief Current window
  std::shared_ptr<sf::RenderWindow> window_;

  /// @brief Icon of the window
  sf::Image icon_;

  /// @brief Deferred events
  EventsDeferrer deferredEvents_;

  /// @brief Game view used to render the game entities
  sf::View gameView_;

  /// @brief HUD view used to render the HUD entities
  /// @example Score, health, etc.
  sf::View hudView_;

  /// @brief Properties of the window
  Properties props_;

  /// @brief Map of shaders
  std::map<std::string, std::shared_ptr<sf::Shader>> shaders_;

  /// @brief Selected shader
  std::shared_ptr<sf::Shader> selectedShader_;

  /**
   * @brief Handle the resize event
   * @param event Resize event
   */
  void HandleResize(const sf::Event &event);
};
}  // namespace mew::managers
