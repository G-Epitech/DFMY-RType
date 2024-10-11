/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** sound_manager.hpp
*/

#pragma once

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <queue>

namespace rtype::client {
class SoundManager {
 public:
  /// @brief Pointer to a sound manager
  using Ptr = std::shared_ptr<SoundManager>;

  /**
   * @brief Create a new sound manager
   * @return Pointer to the sound manager
   */
  static Ptr Create();

  /**
   * @brief Construct a new Window Manager object
   */
  SoundManager();

  /**
   * @brief Construct a new Window Manager object
   */
  ~SoundManager() = default;

  /**
   * @brief Load a sound buffer
   * @param path Path to the sound file
   * @param name Name of the sound
   */
  void LoadSoundBuffer(const std::string& path, const std::string& name);

  /**
   * @brief Play a sound
   * @param name Name of the sound
   */
  void PlaySound(const std::string& name);

  /**
   * @brief Play a music
   * @param path Path to the music file
   */
  void PlayMusic(const std::string& path);

  /**
   * @brief Get the sound volume
   * @return float Volume of the sound
   */
  [[nodiscard]] float GetSoundVolume() const;

  /**
   * @brief Get the music volume
   * @return float Volume of the music
   */
  [[nodiscard]] float GetMusicVolume() const;

  /**
   * @brief Set the sound volume
   * @param volume Volume of the sound
   */
  void SetSoundVolume(const float& volume);

  /**
   * @brief Set the music volume
   * @param volume Volume of the music
   */
  void SetMusicVolume(const float& volume);

  class Exception final : public std::exception {
   public:
    explicit Exception(std::string message);

    [[nodiscard]] const char* what() const noexcept override;

   private:
    std::string message_;
  };

 private:
  /// @brief Map of sound buffers
  std::map<std::string, std::shared_ptr<sf::SoundBuffer>> soundBuffers_{};

  /// @brief Queue of sounds
  std::queue<std::shared_ptr<sf::Sound>> sounds_{};

  /// @brief Queue of musics
  std::queue<std::shared_ptr<sf::Music>> musics_{};

  /// @brief Volume of the sound
  float soundVolume_ = 100;
  /// @brief Volume of the music
  float musicVolume_ = 100;
};
}  // namespace rtype::client
