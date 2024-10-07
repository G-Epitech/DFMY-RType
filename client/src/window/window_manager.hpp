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

namespace rtype::client {
class WindowManager {
 public:
  /// @brief Deferred events
  typedef std::list<sf::Event> EventsDeferrer;

  /// @brief Pointer to a window manager
  typedef std::shared_ptr<WindowManager> Ptr;

  struct Properties {
    std::string title;                    ///< Title of the window
    sf::VideoMode videoMode;              ///< Video mode of the window
    sf::Uint32 style;                     ///< Style of the window
    sf::ContextSettings contextSettings;  ///< Context settings of the window
  };

  /**
   * @brief Create a new window manager
   * @param props Properties of the window
   * @return Pointer to the window manager
   */
  static Ptr Create(Properties &&props);

  /**
   * @brief Construct a new Window Manager object
   * @param props Properties of the window
   */
  explicit WindowManager(Properties &&props);

  /**
   * @brief Construct a new Window Manager object
   * @param props Properties of the window
   */
  ~WindowManager() = default;

  /**
   * @brief Get the Window object
   */
  inline std::shared_ptr<sf::RenderWindow> window() { return window_; }

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
  inline bool IsActive() { return window_ && window_->isOpen(); }

  /**
   * @brief Get deferred events
   * @return Events list that have been deferred
   */
  inline const EventsDeferrer &GetDeferredEvents() { return deferredEvents_; }

 private:
  /// @brief Current window
  std::shared_ptr<sf::RenderWindow> window_;

  /// @brief Deferred events
  EventsDeferrer deferredEvents_;
};
}  // namespace rtype::client
