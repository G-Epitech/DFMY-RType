/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** archetype_manager.hpp
*/

#pragma once

#include <nlohmann/json.hpp>

#include "./archetype_loader/archetype_loader.hpp"
#include "api.hpp"
#include "entity.hpp"
#include "registry.hpp"

namespace zygarde::core::archetypes {
class EXPORT_ZYGARDE_API ArchetypeManager final {
 public:
  ArchetypeManager() = default;
  ~ArchetypeManager() = default;

 public:
  /// @brief Invokation parameters
  struct ScheduleInvocationParams {
    /// @brief Name of the archetype
    std::string archetypeName;
    /// @brief Registry attach callback (what to do after attaching the archetype to the registry)
    /// @param registry Registry to attach the archetype to
    /// @param entity Entity that is spawned
    std::function<void(const std::shared_ptr<zygarde::Registry>&, zygarde::Entity)>
        registryAttachCallback;
  };

 public:
  /**
   * @brief Load archetypes from archetype_directory
   * @param archetype_directory Directories to load archetypes from
   * @param scriptsRegistry Registry of scripts containing script names and their constructors
   */
  void LoadArchetypes(const std::string& archetype_directory,
                      const scripting::types::ScriptsMap& scriptsRegistry);

  /**
   * @brief Invoke an archetype by name
   * @param registry Registry to attach the archetype to
   * @param archetype_name Name of the archetype to invoke
   * @return Entity of the invoked archetype
   */
  zygarde::Entity InvokeArchetype(const std::shared_ptr<zygarde::Registry>& registry,
                                  const std::string& archetype_name);

  /**
   * @brief Schedule an invocation
   * @param params Invocation parameters
   */
  void ScheduleInvocation(const ScheduleInvocationParams& params);

  /**
   * @brief Execute scheduled invokations
   * @param registry Registry to attach the archetypes to
   */
  void ExecuteScheduledInvocations(const std::shared_ptr<zygarde::Registry>& registry);

 private:
  /// @brief Archetype map
  std::map<std::string, std::vector<ArchetypeLoader::RegistryAttachCallback>> archetypes_;
  /// @brief Invokation queue
  std::vector<ScheduleInvocationParams> invokationQueue_;
};
}  // namespace zygarde::core::archetypes
