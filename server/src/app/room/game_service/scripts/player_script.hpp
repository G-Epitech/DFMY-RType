/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PlayerScript.hpp
*/

#pragma once

#include "base/player_base_script.hpp"
#include "game/includes/constants.hpp"
#include "game/includes/stats.hpp"
#include "game/src/utils/projectiles/fire_rate.hpp"
#include "types/weapons.hpp"
#include "zygarde/src/core/types/vector/vector_2f.hpp"
#include "zygarde/src/scripting/components/mono_behaviour/mono_behaviour.hpp"

namespace rtype::server::game::scripts {
static constexpr core::types::Vector3f kPlayerProjectileOffsetPosition{80.0f, 20.0f, 0.0f};
}

namespace rtype::server::game::scripts {
class PlayerScript : public PlayerBaseScript {
 public:
  struct PlayerProps {
    std::string className;
    float powerCooldown;
    std::string primaryWeapon;
    std::string secondaryWeapon;
  };

 public:
  PlayerScript();
  ~PlayerScript() override = default;

  void OnEnable(const scripting::types::ValuesMap& customScriptValues) override;

  void FixedUpdate(const std::shared_ptr<scripting::types::ScriptingContext>& context) override;

  void OnCollisionEnter(const std::shared_ptr<scripting::types::ScriptingContext>& context,
                        const physics::types::Collision2D::ptr& collision) override;

  /**
   * @brief Activate the player's shooting
   */
  inline void Shoot() { isShooting_ = true; }

  /**
   * @brief Set the player's movement direction
   * @param direction The direction to move to
   */
  inline void SetMovementDirection(const core::types::Vector2f& direction) {
    movementDirection_ = direction;
  }

  /**
   * @brief Get the player's score
   * @return The player's score
   */
  [[nodiscard]] inline std::size_t GetScore() const { return score_; }

  /**
   * @brief Add a score to the player
   * @param score The score to add
   */
  inline void IncreaseScore(int score) { score_ += score; }

 private:
  /**
   * @brief Handle the player's movement
   * @param context The scripting context
   */
  void HandleMovement(const std::shared_ptr<scripting::types::ScriptingContext>& context);

 private:
  PlayerProps props_;
  sdk::game::types::WeaponType equippedWeapon_;
  std::chrono::nanoseconds lastShootTime_;
  bool isShooting_;
  std::optional<core::types::Vector2f> movementDirection_;
  int score_{0};
};
}  // namespace rtype::server::game::scripts
