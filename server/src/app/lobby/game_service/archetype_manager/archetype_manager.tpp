/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** archetype_manager.tpp
*/

#pragma once

template <typename Component>
void rtype::server::tools::ArchetypeManager::EmplaceRegistryAttachCallback(
    std::vector<RegistryAttachCallback>* callbacks, Component&& component) {
  callbacks->emplace_back(
      [component = std::forward<Component>(component)](
          zygarde::Entity entity, const std::shared_ptr<zygarde::Registry>& registry) mutable {
        registry->AddComponent<Component>(entity, std::move(component));
      });
}
