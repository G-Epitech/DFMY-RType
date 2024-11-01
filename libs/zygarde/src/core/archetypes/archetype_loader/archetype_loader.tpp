/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** archetype_loader.tpp
*/

#pragma once

template <typename Component>
void zygarde::core::archetypes::ArchetypeLoader::EmplaceRegistryAttachCallback(
    std::vector<RegistryAttachCallback>* callbacks, Component component) {
  callbacks->emplace_back(
      [component](
          zygarde::Entity entity, const std::shared_ptr<zygarde::Registry>& registry) mutable {
        auto copy = component;
        registry->AddComponent<Component>(entity, std::move(copy));
      });
}
