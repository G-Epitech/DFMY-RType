/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** resources_manager.hpp
*/

#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>

namespace rtype::client {

class ResourcesManager {
 public:
  /**
   * @brief Construct a new Resources Manager object
   */
  explicit ResourcesManager();

  /**
   * @brief Destroy the Resources Manager object
   */
  ~ResourcesManager();

  /**
   * @brief Pointer type of the resources manager
   */
  using Ptr = std::shared_ptr<ResourcesManager>;

  class Exception final : public std::exception {
   public:
    /**
     * @brief Construct a new resources manager exception
     * @param msg Message of the exception
     */
    explicit Exception(std::string msg);

    [[nodiscard]] const char *what() const noexcept override;

   private:
    /// @brief Message of the exception
    std::string msg_;
  };

 private:
  /// @brief Map of resources
  struct ResourcesMap {
    /// @brief Map of textures
    std::map<std::string, sf::Texture> textures;
    /// @brief Map of fonts
    std::map<std::string, sf::Font> fonts;
    /// @brief Map of sounds
    std::map<std::string, sf::SoundBuffer> sounds;
  };

  /// @brief Map of resources
  ResourcesMap resourcesMap_;
};
}  // namespace rtype::client
