/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** select.cpp
*/

#include "select.hpp"

#include "./select_container_entity.hpp"
#include "./select_value_entity.hpp"

using namespace rtype::client::ui;
using namespace zygarde::core::components;
using namespace zygarde::core::types;

void Select::Create(const Registry::Ptr& registry, const Select::Properties& props) {
  CreateSelectField(registry, props);
}
void Select::CreateSelectField(const Registry::Ptr& registry, const Select::Properties& props) {
  registry->SpawnEntity<SelectContainerEntity>(props);
  registry->SpawnEntity<SelectValueEntity>(props);
}
void Select::RegisterDependencies(Registry& registry) {
  std::cout << "Registering dependencies" << std::endl;
  SelectContainerEntity::RegisterDependencies(registry);
  SelectValueEntity::RegisterDependencies(registry);
}
