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

#include "./manager_base.hpp"

namespace mew::managers {

class ResourcesManager : public ManagerBase {
 public:
  /// @brief Pointer type of the resources manager
  using Ptr = std::shared_ptr<ResourcesManager>;

  using TexturePtr = std::shared_ptr<sf::Texture>;
  using FontPtr = std::shared_ptr<sf::Font>;
  using ShaderPtr = std::shared_ptr<sf::Shader>;

  /**
   * @brief Construct a new Resources Manager object
   * @param services Managers provider
   */
  explicit ResourcesManager(DependenciesHandler::Ptr services);

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
   */
  void LoadTexture(const std::string &path, const std::string &name);

  /**
   * @brief Load a new shader in the resources manager
   * @param path Shader path to load
   * @param name Name of the shader to store
   * @param type Type of the shader
   */
  void LoadShader(const std::string &path, const std::string &name, sf::Shader::Type type);

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

  /**
   * @brief Get a shader from the resources manager
   * @param name Name of the shader to get
   * @return Shader
   */
  [[nodiscard]] ShaderPtr GetShader(const std::string &name);

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
    /// @brief Map of shaders
    std::map<std::string, ShaderPtr> shaders;
  };

  /// @brief Map of resources
  ResourcesMap resourcesMap_;
};
}  // namespace mew::managers
