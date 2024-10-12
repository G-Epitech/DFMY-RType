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
  /// @brief Pointer type of the resources manager
  using Ptr = std::shared_ptr<ResourcesManager>;

  using TexturePtr = std::shared_ptr<sf::Texture>;
  using FontPtr = std::shared_ptr<sf::Font>;

  /**
   * @brief Create a new resources manager
   * @return Created shared pointer of resources manager
   */
  static Ptr Create();

  /**
   * @brief Construct a new Resources Manager object
   */
  ResourcesManager();

  /**
   * @brief Destroy the Resources Manager object
   */
  ~ResourcesManager();

  /**
   * @brief Load a new font in the resources manager
   * @param path Font path to load
   * @param name Name of the font to store
   * @return True if the font has been loaded, false otherwise
   */
  void LoadFont(const std::string &path, const std::string &name);

  /**
   * @brief Load a new texture in the resources manager
   * @param path Texture path to load
   * @param name Name of the texture to store
   * @return True if the texture has been loaded, false otherwise
   */
  void LoadTexture(const std::string &path, const std::string &name);

  /**
   * @brief Get a texture from the resources manager
   * @param name Name of the texture to get
   * @return Texture
   */
  [[nodiscard]] TexturePtr GetTexture(const std::string &name);

  /**
   * @brief Get a font from the resources manager
   * @param name Name of the font to get
   * @return Font
   */
  [[nodiscard]] FontPtr GetFont(const std::string &name);

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
    std::map<std::string, TexturePtr> textures;
    /// @brief Map of fonts
    std::map<std::string, FontPtr> fonts;
  };

  /// @brief Map of resources
  ResourcesMap resourcesMap_;
};
}  // namespace rtype::client
